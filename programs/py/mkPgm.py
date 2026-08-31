#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4
''' Build the Library
'''


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
import  os
import  sys


sys.path.insert(0, '../../scripts')
import cmnUtil


help_desc   = '''This program builds the library or program by performing the following phases:
    *    Generate the Makefile
    *    Optionally perform mkMisc.py or mkMisc.sh        (default: skip)
    *    Optionally clean the build directory             (default: run)
    *    Compile the necessary objects/modules creating the library or program
    *    Optionally test all the objects                  (default: skip)
    *    Optionally install the library and include files 
         or program                                       (default: run)
    *    Optionally perform mkFinal.py or mkFinal.sh      (default: skip)
The optional phases are controlled by the option arguments below.
This script must always be started from a Bash or Zsh shell
(so CPU_ARCH from .bashrc / .zshrc is visible).
'''
help_epilog = None
help_usage  = None


# ===========================================================================
#                       Command-line entry
# ===========================================================================

class Main(cmnUtil.MainBase):

    def arg_parse_setup(self):
        """ Set up to parse the command line arguments
            Returns: True == continue executing, False == Abort Program
        """
        ok = super().arg_parse_setup()
        if not ok:
            return ok
        self.arg_prs.add_argument('-a', '--arch', action='store', dest='arch',
                             default='CPU_ARCH', help='Makefile Architecture (x86_64 | arm64)'
                             )
        self.arg_prs.add_argument('--no-clean', action='store_false', dest='clean',
                             default=True, help='Skip Clean Phase'
                             )
        self.arg_prs.add_argument('--final', action='store_true', dest='final',
                             default=False, help='Execute mkFinal'
                             )
        self.arg_prs.add_argument('--no-install', action='store_false', dest='install',
                             default=True, help='Skip Install Phase'
                             )
        self.arg_prs.add_argument('--no-make', action='store_false', dest='make',
                             default=True, help='Skip Makefile Generation Phase'
                             )
        self.arg_prs.add_argument('--misc', action='store_true', dest='misc',
                             default=False, help='Execute mkMisc'
                             )
        self.arg_prs.add_argument('--ostype', action='store', dest='ostype',
                             default='macos64', help='Makefile Type (macos64 | win64)'
                             )
        self.arg_prs.add_argument('--test', action='store_true', dest='test',
                             default=False, help='Execute the Tests'
                             )
        return True


    def args_handle(self) -> None:
        """ Handle the command line arguments/flags before executing the
            the main program.
            Command line flags and arguments can be found in self.oArgs.
            Setting a non-zero result_code aborts the program.
        """
        super().args_handle()

        if self.oArgs.arch == 'CPU_ARCH':
            self.oArgs.arch = os.environ.get('CPU_ARCH')
            if self.oArgs.arch is None:
                print('FATAL - No CPU Architecture could be determined!')
                self.result_code = 4
                return


    def exec_pgm(self) -> None:
        """ Program Execution
            Command line flags and arguments can be found in self.oArgs
        """
        self.result_code = 64

        # Build the Makefile.
        if self.oArgs.make:
            if os.path.exists("objects.json.txt"):
                gen_input = "objects.json.txt"
            elif os.path.exists("program.json.txt"):
                gen_input = "program.json.txt"
            else:
                print('ERROR - Could not find genMake input file!')
                self.result_code = 4
                return
            rc = self.do_cmd(f"genMake {gen_input}")
            if rc.returncode != 0:
                print('ERROR - genMake failed!')
                self.result_code = 4
                return
            make_file_name = rc.stdout.strip()
            print(f"\t Makefile: {make_file_name}")
            rc = self.do_cmd(f"cp {make_file_name} Makefile")
            if rc.returncode != 0:
                print('ERROR - cp failed!')
                self.result_code = 4
                return
        if not os.path.exists("Makefile"):
            print('ERROR - Makefile must exist! Run this without --no-make.')
            self.result_code = 4
            return

        # Build the Miscellaneous Enums, Lexers, Parsers, etc if present.
        if self.oArgs.misc and os.path.exists("./mkMisc.py"):
            rc = self.do_cmd("./mkMisc.py")
            if rc.returncode != 0:
                print('ERROR - mkMisc failed!')
                self.result_code = 4
                return
            if not self.oArgs.verbose == 0:
                print(f"{rc.stdout}\n{rc.stderr}")
        elif self.oArgs.misc and os.path.exists("./mkMisc.sh"):
            rc = self.do_cmd("./mkMisc.sh")
            if rc.returncode != 0:
                print('ERROR - mkMisc failed!')
                self.result_code = 4
                return
            if not self.oArgs.verbose == 0:
                print(f"{rc.stdout}\n{rc.stderr}")

        # Build the library.
        if self.oArgs.clean:
            rc = self.do_cmd(f"make -f Makefile clean")
            if rc.returncode != 0:
                print('ERROR - make clean failed!')
                self.result_code = 4
                return
            if not self.oArgs.verbose == 0:
                print(f"{rc.stdout}\n{rc.stderr}")
        rc = self.do_cmd(f"make -f Makefile build")
        if rc.returncode != 0:
            print('ERROR - make build failed!')
            self.result_code = 4
            return
        if not self.oArgs.verbose == 0:
            print(f"{rc.stdout}\n{rc.stderr}")

        # Test the library.
        if self.oArgs.test:
            rc = self.do_cmd(f"make -f Makefile test")
            if rc.returncode != 0:
                print('ERROR - make test failed!')
                self.result_code = 4
                return

        # Install the library.
        if self.oArgs.install:
            rc = self.do_cmd(f"make -f Makefile install")
            if rc.returncode != 0:
                print('ERROR - make install failed!')
                self.result_code = 4
                return
            if not self.oArgs.verbose == 0:
                print(f"{rc.stdout}\n{rc.stderr}")

        # Perform any finalization if needed.
        if self.oArgs.final and os.path.exists("./mkFinal.py"):
            rc = self.do_cmd("./mkFinal.py")
            if rc.returncode != 0:
                print('ERROR - mkFinal.py failed!')
                self.result_code = 4
                return
        elif self.oArgs.final and os.path.exists("./mkFinal.sh"):
            rc = self.do_cmd("./mkFinal.sh")
            if rc.returncode != 0:
                print('ERROR - mkFinal.sh failed!')
                self.result_code = 4
                return

        self.result_code = 0
        return



#############################################################################
#                               Main Program
#############################################################################

if __name__ == "__main__":
    main = Main(help_desc, help_epilog, help_usage)
    main.help_formatter = argparse.RawDescriptionHelpFormatter
    if not main.setup():
        print("FATAL - setup() failed!")
        sys.exit(8)
    main.run()
    sys.exit(int(main.result_code) or 0)
