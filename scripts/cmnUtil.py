#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4

""" Utility Routines

This module contains miscellaneous classes and functions used with in other
scripts.

Version:
    1.1 - Added MainBase Class
    1.2 - Added do_cmd to MainBase

"""


#   This is free and unencumbered software released into the public domain.
#
#   Anyone is free to copy, modify, publish, use, compile, sell, or
#   distribute this software, either in source code form or as a compiled
#   binary, for any purpose, commercial or non-commercial, and by any
#   means.
#
#   In jurisdictions that recognize copyright laws, the author or authors
#   of this software dedicate any and all copyright interest in the
#   software to the public domain. We make this dedication for the benefit
#   of the public at large and to the detriment of our heirs and
#   successors. We intend this dedication to be an overt act of
#   relinquishment in perpetuity of all present and future rights to this
#   software under copyright law.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
#   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
#   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
#   OR OTHER DEALINGS IN THE SOFTWARE.
#
#   For more information, please refer to <http://unlicense.org/>

from __future__ import annotations

import  argparse
import  configparser
import  csv
from    enum    import IntEnum
import  getpass
import  io
import  json
import  logging
import  os
from    pathlib import Path
import  plistlib
import  pwd
import  shlex
import  subprocess
import  sys
import  time
from    typing import Any, Dict, Optional, Union, Sequence, List, Tuple


import  cmn_defs


func_name = lambda n=0: sys._getframe(n + 1).f_code.co_name
# func_name(N) N == stack reference, 0 == current function, 1 == caller, ...
# func_name(0) == current function's name
# func_name(1) == current function caller's name

flg_debug: bool = False
flg_test:  bool = False


#---------------------------------------------------------------------
#                           F l a g s
#---------------------------------------------------------------------

def set_flags(fdebug=False, ftest=False):
    global  flg_debug
    global  flg_test
    flg_debug = fdebug
    flg_test  = ftest

def is_debug() -> bool:
    return flg_debug

def is_test() -> bool:
    return flg_test



#---------------------------------------------------------------------
#       absolute_path -- Convert a Path to an absolute path
#---------------------------------------------------------------------

def absolute_path(
    path_in: str | Path | Sequence[str | Path],
    create_dirs: bool = False,
    check_exists: bool = False,
) -> str | None:
    """
    Convert path_in to an absolute path string.

    Returns:
        Absolute path string on success, or None if the path does not
        exist when check_exists=True (or on type error).
    """
    if flg_debug:
        print(f">>> {sys._getframe().f_code.co_name}")
        print(f"\tpath: {path_in!r}")

    # --- normalize input to a single string ---
    if isinstance(path_in, (str, Path)):
        work_path = str(path_in)
    elif isinstance(path_in, (list, tuple)):
        # Accept mixed str/Path parts
        parts = [str(p) for p in path_in]
        work_path = os.path.join(*parts) if parts else ""
    else:
        return None

    work_path = os.path.expanduser(work_path)
    work_path = os.path.expandvars(work_path)
    work_path = os.path.normpath(work_path)
    work_path = os.path.abspath(work_path)

    if check_exists and not os.path.exists(work_path):
        if flg_debug:
            print(f"\tpath {work_path!r} does not exist!")
        return None

    if create_dirs and not flg_test:
        dir_path = os.path.dirname(work_path)
        if dir_path and not os.path.exists(dir_path):
            os.makedirs(dir_path, exist_ok=True)

    if flg_debug:
        print(f"\tabsolute_path: {work_path!r}")
    return work_path

def path_absolute(
        path_in: str | Path | Sequence[str | Path],
        create_dirs: bool = False, 
        check_exists: bool = False
    ) -> Path | None:
    """ Convert Path to an absolute path

    Returns:
        path string for successful completion or None for error or
            if the path does not exist
    """
    wrk = absolute_path(path_in, create_dirs, check_exists)
    if type(wrk) is str:
        return Path(wrk)
    else:
        return None


#---------------------------------------------------------------------
#       analyze_code -- Analyze Python code in a Directory
#---------------------------------------------------------------------

def analyze_code(dir_path):
    """ Analyze python code in a directory using tools such as
        flake8, pylint, etc.
        Args:
            dir_path: (str) - directory path to search for .py files
    """
    
    dir_path = absolute_path(dir_path)
    if not os.path.isdir(dir_path):
        print(f"ERROR - {dir_path} not found!\n\n", file=sys.stderr)
        return
    python_files = [file for file in os.listdir(dir_path) if file.endswith('.py')]

    if not python_files:
        print(f"WARNING - No Python files found in directory, {dir_path}.\n\n", file=sys.stderr)
        return

    flag_have_flake8 = not do_cmd('which flake8')
    flag_have_pylint = not do_cmd('which pylint')
    if not flag_have_flake8 and not flag_have_pylint:
        print(f"ERROR - Neither flake8 nor pylint are installed!\n\n", file=sys.stderr)
        return

    # Analyze each Python file using pylint and flake8
    for file in python_files:
        file_path = os.path.join(dir_path, file)

        if flag_have_flake8:
            flake8_command = f"flake8 {file_path}"
            subprocess.run(flake8_command, shell=True)

        if flag_have_pylint:
            pylint_command = f"pylint {file_path}"
            subprocess.run(pylint_command, shell=True)


#---------------------------------------------------------------------
#               Comma Separated Values (CSV) Classes
#---------------------------------------------------------------------

class CsvFileReader:
    """ Create a CSV reader that will remove lines from a file that
        begin with '#' or '//' and process each record after it has
        been parsed. This class expects process_record() to be over-
        ridden and for you to call process_csv() with the file path 
        to be processed.
    """

    def _filter_lines(self, filename) -> None:
        """ Filter out the comment lines.
            (Used internally only!)
        """
        rcdnum = 0
        with open(filename, 'r') as file:
            for line in file:
                rcdnum += 1
                if not line.startswith('#') and not line.startswith('//'):
                    yield rcdnum,line

    def process_csv(self, file_path: str) -> None:
        """Process the CSV file, calling process_record() for each record.
        Args:
            filename (str): Path to the CSV file to process.
        """
        # Create a generator of lines (stripping rcdnum for CSV parsing)
        lines = (line for _, line in self._filter_lines(file_path))
        # Wrap lines in StringIO for csv.reader
        self.csv_processor(io.StringIO(''.join(lines)), file_path)

    def csv_processor(self, file_obj, file_path) -> None:
        """Parse CSV content and call process_record for each row.
        Args:
            file_obj: File-like object containing CSV data.
            filename (str): Original filename for retrieving rcdnum.
        """
        reader = csv.reader(file_obj)
        # Re-iterate over _filter_lines to get rcdnum for each line
        rcdnum_iter = (rcdnum for rcdnum, _ in self._filter_lines(file_path))
        for row, rcdnum in zip(reader, rcdnum_iter):
            if self.process_record(rcdnum, row):
                pass
            else:
                break

    def process_record(self, rcdnum: int, record: list) -> bool:
        """ Process a parsed CSV record. Must be overridden in subclasses.
            Args:
                rcdnum (int): Line number in the original file (including comment lines).
                record (list): Parsed CSV record as a list of fields.
            Returns:
                True (bool): Continue processing the file
                False (bool): Abort processing the file
        """
        return False


class CsvReaderToList(CsvFileReader):
    """ Read the input CSV file creating a list of its records.
        usage:
            list_of_records = CsvReaderToList('csv_file_path')
    """

    def __init__(self):
        super().__init__()
        self._records = []

    def __new__(cls, filename):
        obj = super().__new__(cls)
        obj._records = []
        obj.process_csv(filename)
        return obj._records

    def process_record(self, rcdnum: int, record: list) -> bool:
        if record:
            self._records.append(record)
            return True
        return False

    @property
    def records(self):
        return self._records



#---------------------------------------------------------------------
#               dict related routines
#---------------------------------------------------------------------

def dict_diff(d1: dict, d2: dict) -> dict:
    """ Compare two dicts for differences in keys and in key values.
    """
    only_in_d1 = {k: d1[k] for k in d1.keys() - d2.keys()}
    only_in_d2 = {k: d2[k] for k in d2.keys() - d1.keys()}
    changed    = {
        k: (d1[k], d2[k])
        for k in d1.keys() & d2.keys()
        if d1[k] != d2[k]
    }
    return {
        "only_in_first": only_in_d1,
        "only_in_second": only_in_d2,
        "changed": changed
    }



#---------------------------------------------------------------------
#                           OS Execute
#---------------------------------------------------------------------

def do_cmd(cmd_line, cwd='.', flg_sudo=False, flg_fail=False):
    """ Execute an O/S command without capturing input or output.

        cmd - a single string or a list of arguments to be executed
                (use a list which is the best!)

        Returns:
            command return code
    """
    if flg_sudo:
        cmd = f"sudo {cmd_line}"
    else:
        cmd = cmd_line

    if type(cmd) is list:
        args = cmd
    else:
        args = shlex.split(cmd)
    if flg_debug:
        print("do_cmd: ", args)
    if flg_test:
        if flg_debug:
            print("\t Simulating successful: ", args)
        return 0
    result = subprocess.run(
                            args, 
                            cwd=cwd,
                            capture_output=False,
                            shell=True
            )

    if flg_debug:
        print("returncode: ", result.returncode)
    if flg_fail and not result.returncode == 0:
        raise RuntimeError(f"command({args}) returned {result.returncode}!")
    return result.returncode


def do_sys(cmd, cwd=None, shell=True, input=None, flg_sudo=False, flg_trace=True):
    """ Execute an O/S command capturing both, stdout and stderr.
        cmd - a single string or a list of arguments to be executed
                (use a list which is the best!)
        cwd - Current working directory for the subprocess to execute from
        stdin - standard input file handle if needed to supply input to
                the subprocess (generally sys.sysin)
        Returns:
            result.returncode
            result.stdout
            result.stderr
        Note: on MacOS, if shell is True, only the first argument of the cmd list is
        Note: flg_sudo should only be used if passing a string or a true list of arguments 
                in the command.            
    """
    pwd = None
    flg_created_stdin = False
    flg_text = False
    if cwd:
        cwd = absolute_path(cwd)
    if input is not None and type(input) is str:
        flg_text = True
        #stdin = io.StringIO(stdin)
        #flg_created_stdin = True

    if type(cmd) is list:
        args = cmd
    else:
        args = shlex.split(cmd)
    if flg_sudo:
        args.insert(0, "sudo")
    if flg_debug:
        print("do_sys: ", args)
    
    if flg_test:
        if flg_debug:
            print("\t Simulating successful: ", args)
        return subprocess.CompletedProcess(args=args, returncode=0, stderr='', stdout='')
    result = subprocess.run(
                            args, 
                            cwd=cwd,
                            capture_output=True,
                            shell=shell,
                            input=input,
                            text=flg_text
            )
    
    if flg_created_stdin:
        stdin.close()
    if result.stderr is not None:
        stderr = ''
        if type(result.stderr) is bytes:
            stderr = result.stdout.decode('utf-8')
        elif type(result.stderr) is str:
            stdout = result.stderr
        result.stderr = stderr.strip()
    if result.stdout is not None:
        stdout = ''
        if type(result.stdout) is bytes:
            stdout = result.stdout.decode('utf-8')
        elif type(result.stdout) is str:
            stdout = result.stdout
        result.stdout = stdout.strip()
    if flg_debug:
        print("returncode: ", result.returncode)
    return result


def do_sys_io(cmd, cwd=None, shell=True, stdin=None, stderr=None, stdout=None, flg_sudo=False, flg_trace=True):
    """ Execute an O/S command without capturing stdout and stderr.
        cmd - a single string or a list of arguments to be executed
        cwd - Current working directory for the subprocess to execute from
        stdin - standard input file handle if needed to supply input to
                the subprocess (None will default to sys.sysin)
        stderr - standard error output file handle if needed to supply capture from
                the subprocess (None will default to sys.syserr)
        stdout - standard output file handle if needed to supply capture from
                the subprocess (None will default to sys.sysout)
        Returns:
            returncode
        Note: on MacOS, if shell is True, only the first argument of the cmd list is used.
            
    """
    pwd = None
    flg_text = False
    if cwd:
        cwd = absolute_path(cwd)
    if input is not None and type(input) is str:
        flg_text = True
        #stdin = io.StringIO(stdin)
        #flg_created_stdin = True

    if type(cmd) is list:
        args = cmd
    else:
        args = shlex.split(cmd)
    if flg_sudo:
        args.insert(0, "sudo")
    if flg_debug:
        print("do_sys_io: ", args)
    if flg_test:
        if flg_debug:
            print("\t Simulating successful: ", args)
        return subprocess.CompletedProcess(args=args, returncode=0, stderr='', stdout='')
    
    result = subprocess.run(
                            args, 
                            cwd=cwd,
                            capture_output=False,
                            shell=shell,
                            stdin=stdin,
                            stderr=stderr,
                            stdout=stdout,
                            text=flg_text
            )
    
    if flg_trace or flg_debug:
        print("returncode: ", result.returncode)
    return result


#---------------------------------------------------------------------
#                           Error Class
#---------------------------------------------------------------------

class Error:
    """ Error Class for dealing with error messages and method/routine
        completion codes
    """

    def __init__(self, result_code=0, msg=None):
        """ Set the error message.
        """
        self._msg = msg
        self._result_code = result_code

    def error(self):
        """ Return the saved error message.
        """
        return self._msg

    def stderr(self):
        """ Print the saved error message on stderr.
        """
        print(self._msg, file=sys.stderr, flush=True)

    def stdout(self):
        """ Print the saved error message on stderr.
        """
        print(self._msg)


#---------------------------------------------------------------------
#                       Generate a UUID
#---------------------------------------------------------------------

def generate_uuid( ):
    """ Generate a UUID.
    """

    # Do initialization.
    if sys.platform == 'win32':
        szCmd = "uuidgen"
    else:
        szCmd = "uuidgen"

    #  Execute the command.
    if szCmd:
        tupleResult = commands.getstatusoutput( szCmd )
        if flg_debug:
            print(f"\tUUID Result = {tupleResult[0]}, {tupleResult[1]}...")
        if 0 == tupleResult[0]:
            return tupleResult[1]

    # Return to caller.
    raise OSError



#---------------------------------------------------------------------
#               Create an IntEnum from a list
#---------------------------------------------------------------------

def int_enum_create(name: str, members: list[str], start: int = 0) -> type[IntEnum]:
    """Dynamically create an IntEnum from a list of names.
    """
    enum_dict = {}
    for i, member in enumerate(members, start=start):
        enum_dict[member.strip()] = i
    
    return IntEnum(name, enum_dict)



#---------------------------------------------------------------------
#               Javascript Values (JSON) Classes
#---------------------------------------------------------------------

class JsonSqliteReader:
    """
    Reader for SQLite CLI output with -json -noheaders:
    - One JSON row per line
    - May have leading '[' on first line and trailing ']' on last line
    - Skips comment lines starting with #
    - Preserves original line numbers (including comments)
    """
    num_processed: int = 0
    num_warnings:  int = 0

    def process_json(self, filename: str) -> None:
        """Main entry point: process the file line by line"""
        in_data = False
        
        with open(filename, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, start=1):
                line = line.rstrip('\r\n')
                stripped = line.lstrip()
                
                # Skip comments and empty lines
                if not stripped or stripped.startswith('#'):
                    continue
                
                # Remove leading '[' from first data line if present
                if not in_data:
                    if stripped.startswith('[{'):
                        line = line[line.index('{'):]
                    elif stripped.startswith('{'):
                        pass  # clean start
                    else:
                        print(f"Warning: line {line_num} doesn't look like JSON start")
                        continue
                    in_data = True
                
                # Remove trailing ']' from last line if present
                if stripped.endswith('}]') or stripped.endswith(']'):
                    line = line.rstrip(']} \t')
                
                if not line.strip():
                    continue
                
                try:
                    record: Dict = json.loads(line)
                    if self.process_record(line_num, record):
                        self.num_processed += 1
                    else:
                        self.num_warnings += 1

                except json.JSONDecodeError as e:
                    print(f"JSON error on line {line_num}: {e}")
                    print(f"  Content: {line[:80]!r}...")
                    self.num_warnings += 1
                    continue

    def process_record(self, line_number: int, record: Dict[str, Any]) -> None:
        """
        Override this method in subclasses.
        record is a dict (one SQLite row)
        Returns:    True or False to imply successful completion
        """
        #raise NotImplementedError("You must implement process_record()")
        return Fale



#---------------------------------------------------------------------
#               Various routines for manipulating lists
#---------------------------------------------------------------------

def list_insert_before_marker_if_needed(
    lines: list[str],
    marker: str,
    line_to_insert: str,
) -> bool:
    """ Insert a line before the line that contains the marker.
        Returns True if inserted, False if already present or marker not found.
    """
    normalized_insert = line_to_insert.rstrip("\n")

    # Pass 1: already present?
    for line in lines:
        if normalized_insert == line.rstrip("\n"):
            return False

    # Pass 2: find place to insert
    for i, line in enumerate(lines):
        if marker in line:
            lines.insert(i, line_to_insert)
            return True

    return False


#---------------------------------------------------------------------
#                       Path Tweaks Class
#---------------------------------------------------------------------

class PathTweaks(Path):
    """ Extended pathlib.Path with useful utility methods.
    """
    debug_mode: bool = False   # True → lots of status messages
    test_mode: bool  = False   # True → show commands but skip execution

    @property
    def debug(self) -> bool:
        return self.debug_mode

    @debug.setter
    def debug(self, value: bool) -> None:
        self.debug_mode = bool(value)

    @property
    def test(self) -> bool:
        return self.test_mode

    @test.setter
    def test(self, value: bool) -> None:
        self.test_mode = bool(value)

    @classmethod
    def absolute(cls, path_in: str | Path, create_dirs: bool = False, check_exists: bool = False):
        """Convert str or Path to an absolute path.

        Returns:
            PathTweaks object on success
            None if check_exists=True and path does not exist
            None if input type is unsupported
        """
        if self.flg_debug or self.flg_test:
            print(f">>> PathTweaks.absolute", file=sys.stderr)
            print(f"    input: {path_in} ({type(path_in).__name__})", file=sys.stderr)

        # --- Input handling ---
        if isinstance(path_in, Path):
            work = str(path_in)
        elif isinstance(path_in, str):
            work = path_in
        else:
            if self.flg_debug:
                print(f"    Error: Unsupported type {type(path_in)}", file=sys.stderr)
            return None

        # --- Expansions and normalization ---
        work = os.path.expanduser(work)
        work = os.path.expandvars(work)
        work = os.path.normpath(work)
        work = os.path.abspath(work)

        # --- Existence check ---
        if check_exists and not os.path.exists(work):
            if self.flg_debug:
                print(f"    Path does not exist: {work}", file=sys.stderr)
            return None

        # --- Create directories if requested ---
        if create_dirs and not flg_test:
            parent = os.path.dirname(work)
            if parent and not os.path.exists(parent):
                try:
                    os.makedirs(parent)
                except OSError as e:
                    if self.flg_debug:
                        print(f"    Failed to create directories: {e}", file=sys.stderr)
                    return None

        if self.flg_debug or self.flg_test:
            print(f"    absolute_path: {work}", file=sys.stderr)

        return cls(work)

    # Instance convenience method
    def to_absolute(self, create_dirs: bool = False, check_exists: bool = False):
        """ Instance version: makes it easy to call on an existing PathTweaks object.
        """
        return self.absolute(self, create_dirs=create_dirs, check_exists=check_exists)



#---------------------------------------------------------------------
#                       Support Base Class
#---------------------------------------------------------------------

class SupportBase:
    """
    SupportBase provides common utility methods:
    - debug / test mode control
    - safe path resolution
    - external command execution
    - fatal error handling
    """

    debug_mode: bool = False   # True → lots of status messages
    test_mode: bool  = False   # True → show commands but skip execution

    def __init__(
            self, 
            debug: bool = False, 
            test: bool = False
        ):
        if debug:
            print(f"SupportBase:init(debug: {debug} test: {test})")
        self.debug_mode = debug
        self.flg_debug  = debug
        self.test_mode  = test
        self.flg_test   = test
        self.stderr     = sys.stderr
        self.stdout     = sys.stdout

    def __str__(self) -> str:
        return (
            f"{self.__class__.__name__}("
            f"debug_mode={self.debug_mode}, "
            f"test_mode={self.test_mode})"
        )

    def __repr__(self) -> str:
        return f"<{self.__str__()}>"

    @property
    def debug(self) -> bool:
        return self.debug_mode

    @debug.setter
    def debug(self, value: bool) -> None:
        self.debug_mode = bool(value)
        self.flg_debug  = bool(value)

    @property
    def test(self) -> bool:
        return self.test_mode

    @test.setter
    def test(self, value: bool) -> None:
        self.test_mode = bool(value)
        self.flg_test  = bool(value)

    def absolute_path(
        self,
        path_in: Union[str, Path, os.PathLike],
        *,
        create_dirs: bool = False,
        check_exists: bool = False,
    ) -> Optional[Path]:
        """
        Convert input to an absolute path.
        Optionally expand ~ / env vars, create missing parent dirs, check existence.

        Returns:
            Absolute path string or None on error/invalid input
        """
        if self.debug_mode:
            print(f">>> {self.__class__.__name__}.absolute_path({path_in!r})", file=self.stderr)

        try:
            # 1. Convert to string and expand environment variables FIRST
            path_str = os.fspath(path_in)                    # handles Path, str, os.PathLike
            expanded = os.path.expandvars(path_str)          # ← This was missing
            expanded = os.path.expanduser(expanded)          # expand ~ after vars (safer order)

            # 2. Now turn it into a Path and resolve
            p = Path(expanded).resolve(strict=False)
            
            if check_exists and not p.exists():
                if self.debug_mode:
                    print(f"  Path does not exist: {p}", file=self.stderr)
                return None

            if create_dirs and not self.test_mode:
                p.parent.mkdir(parents=True, exist_ok=True)

            result = str(p)

            if self.debug_mode:
                print(f"  → {result}", file=self.stderr)

            return p

        except Exception as e:
            if self.debug_mode:
                print(f"  Failed to resolve path: {e}", file=self.stderr)
            return None

    def add_method(cls, name: str):
        """ This will add several different types of methods to
            a class but needs to be followed by several different
            commands:

            @add_method(Person, "greet") # Adds method to all instances

            def greet(self, greeting="Hello"):
                return f"{greeting}, {self.name}!"


            @add_classmethod(Person, "get_population") # Adds a class method

            def get_population(cls):
                return f"There are currently {cls.population} people."
        """
        def decorator(func):
            setattr(cls, name, func)
            return func
        return decorator    

    def do_cmd(
        self,
        cmd_line: str,
        cwd: Union[str, Path] = ".",
        *,
        fatal: bool = False,
        capture: bool = True,
        shell: bool = True,
    ) -> Optional[subprocess.CompletedProcess]:
        """
        Execute external command. Returns True on success (rc == 0).

        In test_mode: just prints the command and returns True.
        In debug_mode: shows detailed execution info.
        If fatal == True and command fails → calls fatal_error()
        Returns: subprocess.CompletedProcess:
            returncode
            stdout
            stderr
        """
        if self.debug_mode:
            print(f">>> {self.__class__.__name__}.do_cmd({cwd!r}, {cmd_line!r})", file=self.stderr)

        if self.test_mode:
            print(f"(TEST MODE) cd {cwd} && {cmd_line}   [skipped]", file=self.stderr)
            return None

        try:
            cwd_path = Path(cwd).resolve()
            result = subprocess.run(
                cmd_line,
                shell=shell,
                cwd=str(cwd_path),
                text=True,
                capture_output=capture,
                check=False,
            )

            if self.debug_mode:
                print(f"  rc = {result.returncode}", file=self.stderr)
                if result.stdout: 
                    print(f"  stdout: '{result.stdout.strip()}'", file=self.stderr)
                if result.stderr: 
                    print(f"  stderr: '{result.stderr.strip()}'", file=self.stderr)

            if result.returncode != 0:
                msg = f"Command failed (rc={result.returncode}): {cmd_line}"
                if fatal:
                    self.fatal_error(64, msg)
                else:
                    print(f"ERROR - {msg}", file=self.stderr)
                    if result.stdout and not self.debug_mode:
                        print(f"stdout → '{result.stdout.strip()}'", file=self.stderr)
                    if result.stderr and not self.debug_mode:
                        print(f"stderr → '{result.stderr.strip()}'", file=self.stderr)
            return result

        except Exception as e:
            msg = f"Failed to run command '{cmd_line}': {e}"
            if fatal:
                self.fatal_error(65, msg)
            print(f"ERROR - {msg}", file=self.stderr)
            # Not sure if we have a result object here.
            return None

    def exists(self, path_in: Union[str, Path, os.PathLike]) -> bool:
        return self.absolute_path(path_in).exists()

    def fatal_error(self, exit_code: int = 1, message: Optional[str] = None) -> None:
        """Print message to stderr and exit the process."""
        msg = message or "A fatal error occurred"
        print(f"FATAL: {msg}", file=self.stderr)
        sys.exit(exit_code)
    
    def delete_if_exists(self, path_in: Union[str, Path, os.PathLike]):
        work = self.absolute_path(path_in)
        if work.exists():
            if work.is_dir():
                self.do_cmd(f"rm -fr {work.name}")
            elif work.is_file():
                self.do_cmd(f"rm {work.name}")
            else:
                pass




#---------------------------------------------------------------------
#                       Main Command Class
#---------------------------------------------------------------------

class MainBase(SupportBase):
    """ Base Command Line Program Class

        The normal sequence to use this class is to inherit it and over-
        ride exec_pgm(). If you need to add more command line arguments,
        the override arg_parse_setup() but make sure that the first
        statement is 'super().arg_parse_setup()'. Creating and running
        the class would normally be as follows assuming class Main inherits
        from MainBase:
                oMain = cmnUtil.Main()
                if not oMain.setup():
                    print('FATAL - Main::setup() failed!')
                    sys.exit(8)
                oMain.run()
                sys.exit(int(oMain.return_code))

                
    """

    def __init__(self, desc=None, epilog=None, usage=None, *args, **options):
        """ Initialize a new MainBase Instance.
        """
        super().__init__()
        self.oArgs = None
        self._desc = desc
        self._epilog = epilog
        self._usage = usage
        self.help_formatter = argparse.HelpFormatter
        self.result_code = 128
        self.verbose = 0
        self.stderr = sys.stderr
        self.stdout = sys.stdout
        self.program_path = sys.argv[0]
        self.cli_args = sys.argv[1:]
        
        # Set up logging.
        self.start_time = time.time( )

    @property
    def desc(self) -> str:
        return self._desc

    @desc.setter
    def desc(self, value: str) -> None:
        self._desc = value

    @property
    def epilog(self) -> bool:
        return self._epilog

    @epilog.setter
    def epilog(self, value: str) -> None:
        self._epilog = value

    @property
    def usage(self) -> bool:
        return self._usage

    @usage.setter
    def usage(self, value: str) -> None:
        self._usage = value

    def arg_parse_create(self):
        """ Create the argument parser.
        """
        self.arg_prs =  argparse.ArgumentParser(
                            description=self._desc, 
                            epilog=self._epilog, 
                            usage=self._usage,
                            formatter_class=self.help_formatter,
                        )
        if self.arg_prs is None:
            return False
        return True

    def arg_parse_exec(self):
        """ Setup and execute the argument parsing.
        """
        if not self.arg_parse_create():
            self.fatal_error(4,'Main::arg_parse_create() failed!')
        if not self.arg_parse_setup():
            self.fatal_error(4,'Main::arg_parse_setup() failed!')
        if not self.arg_parse_parse():
            self.fatal_error(4,'Main::arg_parse_parse() failed!')
        return True

    def arg_parse_post(self):
        """ This method is called after the arguments have been parsed
            and debug mode has been set. This allows the application
            to preprocess any arguments if needed.
            Returns: True == continue executing, False == Abort Program
        """
        return True

    def arg_parse_parse(self):
        """ Parse the command line arguments. This is when help will be
            recognized. So, epilog and usage need to be set before this
            method is called.
            Returns: True == continue executing, False == Abort Program
        """
        rc = True
        if self._epilog is not None and len(self._epilog) > 0:
            self.arg_prs.epilog = self._epilog
        if self._usage is not None and len(self._usage) > 0:
            self.arg_prs.usage = self._usage
        self.oArgs = self.arg_prs.parse_args(self.cli_args)
        if hasattr(self, 'oArgs') and self.oArgs:
            if hasattr(self.oArgs, 'debug_mode') and self.oArgs.debug_mode:
                print("In DEBUG Mode...")
                print('Args:', self.oArgs)
                self.debug_mode = True
                self.flg_debug = True
            if hasattr(self.oArgs, 'test_mode') and self.oArgs.test_mode:
                self.test_mode = True
                self.flg_test = True
            if hasattr(self.oArgs, 'verbose') and self.oArgs.verbose:
                self.verbose = self.oArgs.verbose
        else:
            rc = False
        if rc:
            rc = self.arg_parse_post()
        return rc

    def arg_parse_setup(self) -> bool:
        """ Set up to parse the command line arguments
            Returns: True == continue executing, False == Abort Program
        """
        # Keyword Arguments
        self.arg_prs.add_argument('-d', '--debug', action='store_true', dest='debug_mode',
                                  default=False, help='Set debug mode (default: False)'
                                 )
        self.arg_prs.add_argument('-f', '--force', action='store_true', dest='flg_force',
                                  default=False, help='Set force mode'
                                 )
        self.arg_prs.add_argument('--test_mode', action='store_true', dest='test_mode',
                                  default=False, help='Set test mode (ie no actual updating)(default: False)'
                                 )
        self.arg_prs.add_argument('-v', '--verbose', action='count', default=0,
                                  dest='verbose', help='increase output verbosity (default: 0)'
                                 )
        self.arg_prs.add_argument('--version', action='store_true', default=False,
                                  dest='version', help='Display the program''s version'
                                 )
        # Positional Arguments
        flg = self.arg_parse_setup_positional()
        return flg

    def arg_parse_setup_positional(self) -> bool:
        """ Set up to parse the positional command line arguments. These
            arguments must be presented in order. So, override this if you
            want to add specific positional arguments before the the catch-all 
            of 'args' and call this method at the end of your method or skip
            this method if you do not want the catch-all 'args' (ie positional
            arguments are not needed).
            Returns: True == continue executing, False == Abort Program
        """
        #self.arg_prs.add_argument('name', nargs=1, default='', help='Name (Required)') <= Example
        self.arg_prs.add_argument('args', nargs=argparse.REMAINDER, default=[], help="Remaining Arguments")
        return True

    def args_handle(self) -> None:                              #pylint: disable=no-self-use
        """ Handle the command line arguments/flags before executing the
            the main program.
            Command line flags and arguments can be found in self.oArgs.
            Setting a non-zero result_code aborts the program.
        """
        self.result_code = 0

    def display_version(self):
        """ Display the help for this program and exit.
        """
        print(f"{self.get_version_string()}", file=sys.stderr)
        sys.exit(4)

    def do_help(self):
        """ Display the help for this program and exit.
        """
        self.arg_prs.print_help()
        os.exit(8)

    def exec_pgm(self) -> None:                         #pylint: disable=no-self-use
        """ Program Execution
            Command line flags and arguments can be found in self.oArgs
            Warning - Main should override this method and make certain that
            it returns an exit code in self.result_code.
        """
        self.result_code = 24
        self.fatal_error(24, 'MainBase::exec_pgm() is NOT implemented!')

    def get_version_string(self, default="0.0.0") -> str:
        """ Return version as string like '1.3.14a' if pgm_version exists, 
            else default.
        """
        if 'pgm_version' not in globals():
            return default
        
        version = globals()['pgm_version']
        
        # Check if it's a list or tuple with 1 to 4 parts
        if not isinstance(version, (list, tuple)):
            return default
        
        # Convert each part to string and join with dots
        try:
            version_parts = [str(part).strip() for part in version]
            return '.'.join(version_parts)
        except Exception:
            return default

    def run(self):
        """ Run the program keeping track of how long that it takes.
        """

        # arguments and options are in self.oArgs.
        fRc = self.arg_parse_exec()
        if not fRc:
            self.fatal_error(4, 'Something was wrong with the command line arguments!')
        # arguments and options are in self.oArgs.
        #print(f"oArgs: {self.oArgs}", file=self.stderr)
        if hasattr(self, 'oArgs') and hasattr(self.oArgs, 'version') and self.oArgs.version:
            self.display_version()
        self.args_handle()
        if self.result_code > 0:
            self.fatal_error(4, 'Something was wrong with the command line arguments!')

        if hasattr(self, 'oArgs') and self.oArgs:
            if hasattr(self.oArgs, 'flg_debug') and self.oArgs.flg_debug:
                print("\tIn Debug Mode", file=sys.stderr)
                self.flg_debug = True
                flg_debug = True
            if hasattr(self.oArgs, 'flg_version') and self.oArgs.flg_version:
                if 'program_version' in globals():
                    print(f"Program Version: {program_version}")
                    sys.exit(0)

        self.exec_pgm()
        '''
        WARNING: while this might be a way of handling errors, it hides syntax error
                 and does not give the statement back trace.
        try:
            self.exec_pgm()
        except Exception as excp:  # pylint: disable=broad-except
            if self.flg_debug:
                print("Exception in exec_pgm(): ", excp, file=sys.stderr) 
            #print("Exception:", excp)
            self.result_code = 20
        '''
            
        end_time = time.time()
        if hasattr(self, 'oArgs') and self.oArgs:
            if (hasattr(self.oArgs, 'flg_debug') and self.oArgs.flg_debug) or (hasattr(self.oArgs, 'verbose') \
                    and self.oArgs.verbose):
                if int(self.result_code) == 0:
                    print("...Successful completion.")
                else:
                    print("...Completion Failure of %d" % self.result_code)
                print("Start Time: %s" % time.ctime(self.start_time))
                print("End   Time: %s" % time.ctime(end_time))
                diff_time = end_time - self.start_time      # float Time in seconds
                secs = int(diff_time % 60.0)
                mins = int((diff_time / 60.0) % 60.0)
                hrs = int(diff_time / 3600.0)
                print("run   Time: %d:%02d:%02d" % (hrs, mins, secs))

    def setup(self):
        """ Setup to run the program.
            Argparse parameters must be set up before this.
        """
        return True



######################################################################
#                       Path Manipulations
######################################################################

#---------------------------------------------------------------------
#               Find Owner's name for a directory
#---------------------------------------------------------------------

def path_owner(file_path):
    """ Find the owner for a given file path.
        Returns:
            file path's ownwer's user name if successful or None
    """
    owner = None
    absolute = absolute_path(file_path)
    if absolute is not None:
        if os.path.exists(absolute):
            file_stats = os.stat(file_path)
            try:
                uid = file_stats.st_uid
                owner = pwd.getpwuid(uid).pw_name
            except:
                owner = None
    return owner


#---------------------------------------------------------------------
#   Select Files from a Directory given a prefix and/or suffix.
#---------------------------------------------------------------------

def selectFilesFromDir(dir_path, prefix='', suffix=''):
    """ Select Files from a Directory given a prefix and/or suffix
    """
    if dir_path is None:
        return None
    if 0 == len(dir_path):
        return None
    dir_path = absolute_path(dir_path)
    if not os.path.isdir(dir_path):
        return None
    # Scan the directory
    list_dir = os.listdir(dir_path)
    list_selection = [ ]
    for file_name in list_dir:
        if len(prefix) and prefix == file_name[0:len(prefix)]:
            pass
        else:
            continue
        if len(suffix) and suffix == file_name[-len(suffix):]:
            pass
        else:
            continue
        list_selection.append(file_name)

    return list_selection



######################################################################
#               MacOS Plist Manipulations
######################################################################

def plist_from_file(file_path):
    """ Convert a physical plist file into internal dict or list format
        that can be processed by python programs.
        Returns:
            A dict or list if successful or None if not
    """
    plist = None
    absolute = absolute_path(file_path)
    if absolute is not None:
        if os.path.exists(absolute):
            with open(absolute, "r") as file:
                plist_data = file.read().strip()
                if flg_trace:
                    print(f"\tplist_data(raw): '{plist_data}'")
                if plist_data is None or len(plist_data) == 0:
                    return None
                if type(plist_data) is str:
                    plist_data = bytes(plist_data, "utf-8")
                try:
                    plist = plistlib.loads(plist_data)
                    if flg_trace:
                        print(f"\tplist: '{plist}'")
                except Exception as e:
                    if flg_trace:
                        print(f"\tException: {e}")
                    plist = None
                if plist is not None and (type(plist) is dict or type(plist) is list):
                    pass
                else:
                    if flg_trace:
                        print(f"\tplist: '{plist}'")
                        print(f"\t{absolute} failed check for dict or list!")
                    plist = None
    return plist



######################################################################
#           get Various types of Replies from the console
######################################################################

def replyHidden(szDesc='Password'):
    """ get a string from the console.

        Note: getpass does not use stdin/stderr/stdout on macOS!
    """

    print(f"{szDesc} (or 'none' to skip ):")
    szReply = getpass.getpass(prompt="")    # 
    if szReply == 'none' or len(szReply) == 0:
        return None
    if flg_debug or fTrace:
        print(f"\tszReply: {szReply}")
    return szReply


def replyListInt(szDesc, iLow, iHigh, dictOptions={'none':None}, stdin=sys.stdin, stdout=sys.stdout):
    """ Get an integer from the console. An optional dictionary can
        be supplied that translate a character string to hopefully
        a mumber since that is what the calling routine expects.
    
        Returns:    None or integer
    """

    while True:
        if szDesc:
            print(szDesc,file=stdout,flush=True)
        print(  f"Please enter an integer from {iLow} to {iHigh} (or {dictOptions.keys()} ):",
                file=stdout, 
                flush=True
        )
        szReply = stdin.readline( ).strip( )
        if dictOptions.has_key(szReply):
            oReply = dictOptions[szReply]
            break
        if szReply.isdigit( ):
            iReply = int( szReply )
            if (iReply >= iLow) and (iReply <= iHigh):
                return iReply
            else:
                print(
                        f"ERROR - {szReply} is not within range! Pls try again...", 
                        file=stdout, 
                        flush=True
                )
        else:
            print(
                    f"ERROR - {szReply} is not numeric! Pls try again...", 
                    file=stdout, 
                    flush=True
            )

    return oReply


def replyPause(szDesc=None, stdin=sys.stdin, stdout=sys.stdout):
    """ get reply from the console to supply a pause in script execution.
        For instance, you could use this if you are trying to paginate
        output from the script.
    """
    global      flg_debug

    if szDesc:
        print(szDesc)
    print("Please press any key to proceed...", file=stdout, flush=True)
    szReply = stdin.readline( ).strip( )

    return None


def replySelection(szDesc, listSelection, dictOptions={'none':None}):
    """ get a selection from the console.
            listSelection is simply a list of strings
    
        Returns: item # (relative to 1) or value of the options
    """

    if 0 == len(listSelection):
        return None

    listDisplay = [ ]
    i = 1
    for szItem in listSelection:
        listDisplay.append( "%2d - %s" % ( i, szItem ) )
        i += 1

    if szDesc:
        print(szDesc)
    for szLine in listDisplay:
        print(szLine)
    iReply = getReplyInt( None, 1, len(listSelection), dictOptions )
    return iReply


def replySelectionMulti( szDesc, dictSelections, dictOptions={'none':None} ):
    """ get a selection from the console.
            dictSelection has the selection items for keys and values of True or False
                indicating whether the value was selected.
    
        Returns: item # (relative to 1) or value of the options
    """

    if 0 == len(dictSelections):
        return (None,None)

    listSelections = dictSelections.keys( )
    listSelections.sort( )

    while True:
        if szDesc:
            print(szDesc)
        i = 1
        for szItem in listSelections:
            selected = ' '
            if dictSelections[szItem]:
                selected = '*'
            print("%s %2d - %s" % ( selected, i, szItem ))
            i += 1
            iLow = 1
            iHigh = len(listSelections)
        while True:
            print("Please enter an integer from %d to %d (or %s ):" \
                    % (iLow,iHigh,dictOptions.keys()))
            szReply = sys.stdin.readline( ).strip( )
            if dictOptions.has_key(szReply):
                oReply = dictOptions[szReply]
                listSelected = [ ]
                for szItem in listSelections:
                    if dictSelections[szItem]:
                        listSelected.append(szItem)
                return (oReply,listSelected)
            if szReply.isdigit( ):
                iReply = int( szReply )
                if (iReply >= iLow) and (iReply <= iHigh):
                    if dictSelections[listSelections[iReply-1]]:
                        dictSelections[listSelections[iReply-1]] = False
                    else:
                        dictSelections[listSelections[iReply-1]] = True
                    break
                else:
                    print("ERROR - %s is not within range! Pls try again..." % ( szReply ))
            else:
                print("ERROR - %s is not numeric! Pls try again..." % ( szReply ))


def replyString(szDesc, stdin=sys.stdin, stdout=sys.stdout):
    """get a string from the console."""

    if szDesc:
        print(szDesc)
    print("Please enter the string (or 'none' to skip ):", file=stdout)
    szReply = stdin.readline( ).strip( )
    if szReply == 'none':
        return None
    if len(szReply) > 0:
        return szReply

    return None


def reply_yn(szDesc, szDefault='y', stdin=sys.stdin, stdout=sys.stdout):
    """ Get a yes/no reply from the console.
        returns:
            1 == Yes
            0 == No
        example:
            ans = util.reply_yn("Do you want to proceed")
            if ans:
                print("Proceeding!")
            else:
                print("Terminating!")
    """

    if szDefault:
        if ('n' == szDefault) or ('y' == szDefault):
            if 'n' == szDefault:
                szDft = ('N','y')
            if 'y' == szDefault:
                szDft = ('Y','n')
        else:
            raise ValueError
    else:
        szDft = ('Y','n')
    szMsgYN = "(%s, %s or 'none' to skip)" % szDft

    while 1:
        szMsg = "%s %s? " % (szDesc,szMsgYN)
        print(szMsg, file=stdout)
        szReply = stdin.readline( ).strip( )
        if '' == szReply:
           szReply = szDefault
        if szReply == 'none':
           break
        if ('y' == szReply) or ('Y' == szReply) or ('yes' == szReply) or ('Yes' == szReply):
            return 1
        if ('n' == szReply) or ('N' == szReply) or ('no' == szReply) or ('No' == szReply):
            return 0
        print(f"ERROR - {szReply} is an invalid response! Please try again...", file=stdout)

    return None



######################################################################
#                       Search the python path
######################################################################

def search_python_path(filename):
    for dir in sys.path:
        filepath = os.path.join(dir, filename)
        if os.path.exists(filepath):
            return filepath
    return None


######################################################################
#                       String Manipulation
######################################################################

def to_camel(s: str) -> str:
    """ Camelize a string (ie First character is upper case and
        remaining characters are lower case in each word and
        join all words).
    """
    parts = s.replace("-", " ").replace("_", " ").split()
    if not parts:
        return ""
    return parts[0].lower() + "".join(word.capitalize() for word in parts[1:])



######################################################################
#                           User / Group
######################################################################

def group_name():
    result = util.do_sys('id -gn',sudo=True)
    if result.returncode:
        return None
    id_user = result.stdout.strip().decode('ASCII')
    return id_user

def user_name():
    result = util.do_sys('id -un',sudo=True)
    if result.returncode:
        return None
    id_user = result.stdout.strip().decode('ASCII')
    return id_user


################################################################################
#                           Command-line interface
################################################################################

if __name__ == '__main__':
    print("Error: Sorry, util.py provides classes and functions for use by other scripts.")
    print("\tIt is not meant to be run by itself.")
    sys.exit(4)
