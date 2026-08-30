// vi:nu:et:sts=4 ts=4 sw=4


static
int             nDefine = 0;        /* Number of -D options on the command line */
static
char            **azDefine = 0;     /* Name of the -D macros */


/* This routine is called with the argument to each -D command-line option.
** Add the macro defined to the azDefine array.
*/
static
void            handle_D_option (
    char            *z
)
{
    char            **paz;
    
    nDefine++;
    azDefine = (char **)realloc(azDefine, (sizeof(azDefine[0]) * nDefine));
    if (azDefine == NULL) {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }
    paz = &azDefine[nDefine-1];
    *paz = (char *) malloc( lemon_Strlen(z)+1 );
    if ( *paz == NULL ) {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }
    lemon_strcpy(*paz, z);

    // Split string if '=' is found.
    for (z=*paz; *z && (*z != '='); z++) 
        ;
    *z = 0;
}



    static
    OPTIONS_T       options[] = {
        {OPT_FLAG, "b", (char*)&basisflag, "Print only the basis in report."},
        {OPT_FLAG, "c", (char*)&compress, "Don't compress the action table."},
        {OPT_FLAG, "d", (char*)&fDebug, "Display debug information (very verbose)."},
        {OPT_FSTR, "D", (char*)handle_D_option, "Define an %ifdef macro."},
        {OPT_FSTR, "f", 0, "Ignored.  (Placeholder for -f compiler options.)"},
        {OPT_FLAG, "g", (char*)&rpflag, "Print grammar without actions."},
        {OPT_FSTR, "I", 0, "Ignored.  (Placeholder for '-I' compiler options.)"},
        {OPT_FLAG, "m", (char*)&mhflag, "Output a makeheaders compatible file."},
        {OPT_FLAG, "l", (char*)&nolinenosflag, "Do not print #line statements."},
        {OPT_FSTR, "O", 0, "Ignored.  (Placeholder for '-O' compiler options.)"},
        {OPT_FLAG, "p", (char*)&showPrecedenceConflict,
                        "Show conflicts resolved by precedence rules"},
        {OPT_FLAG, "q", (char*)&quiet, "(Quiet) Don't print the report file."},
        {OPT_FLAG, "r", (char*)&noResort, "Do not sort or renumber states"},
        {OPT_FLAG, "s", (char*)&statistics,
                                       "Print parser stats to standard output."},
        {OPT_FLAG, "u", (char*)&fUseHeader, "Use Header Template."},
        {OPT_FLAG, "x", (char*)&version, "Print the version number."},
        {OPT_FSTR, "T", (char*)handle_T_option, "Specify a template file."},
        {OPT_FSTR, "W", 0, "Ignored.  (Placeholder for '-W' compiler options.)"},
        {OPT_FLAG,0,0,0}
    };



enum option_type {
    OPT_FLAG=1,
    OPT_INT,
    OPT_DBL,
    OPT_STR,
    OPT_FFLAG,
    OPT_FINT,
    OPT_FDBL,
    OPT_FSTR
};


typedef struct s_options {
    enum option_type type;
    const
    char            *label;
    char            *arg;
    const
    char            *message;
} OPTIONS_T;



int             OptInit (
    LEMON_T         *pLem,
    char            **,
    OPTIONS_T       *,
    FILE            *
);
int         OptNArgs(void);
char        *OptArg(int);
void        OptErr(int);
void        OptPrint(void);



/************************ From the file "option.c" **************************/
static
char            **argv;
static
OPTIONS_T       *op;
static
FILE            *errstream;

#define ISOPT(X) ((X)[0]=='-'||(X)[0]=='+'||strchr((X),'=')!=0)

/*
** Print the command line with a carrot pointing to the k-th character
** of the n-th field.
*/
static
void            errline (
    int             n,
    int             k,
    FILE            *err
)
{
    int             spcnt, i;
    
    if (argv[0])
        fprintf(err, "%s", argv[0]);

    spcnt = lemon_Strlen(argv[0]) + 1;

    for (i=1; i<n && argv[i]; i++) {
        fprintf(err," %s",argv[i]);
        spcnt += lemon_Strlen(argv[i])+1;
    }
    spcnt += k;
    for (; argv[i]; i++)
        fprintf(err," %s",argv[i]);
    if (spcnt < 20) {
        fprintf(err,"\n%*s^-- here\n",spcnt,"");
    } else {
        fprintf(err,"\n%*shere --^\n",spcnt-7,"");
    }
}



/*
** Return the index of the N-th non-switch argument.  Return -1
** if N is out of range.
*/
static
int             argindex (
    int             n
)
{
    int             i;
    int             dashdash = 0;

    if ((argv != 0) && (*argv != 0)) {
        for (i=1; argv[i]; i++) {
            if ( dashdash || !ISOPT(argv[i]) ) {
                if ( n == 0 ) 
                    return i;
                n--;
            }
            if ( strcmp(argv[i],"--") == 0 ) 
                dashdash = 1;
        }
    }
    return -1;
}



static 
char            emsg[] = "Command line syntax error: ";



/*
** Process a flag command line argument.
*/
static
int             handleflags (
    LEMON_T         *pLem,
    int             i,
    FILE            *err
)
{
    int v;
    int errcnt = 0;
    int j;

    for (j=0; op[j].label; j++) {
        if (strncmp(&argv[i][1],op[j].label,lemon_Strlen(op[j].label)) == 0) 
            break;
    }
    v = argv[i][0] == '-' ? 1 : 0;
    if ( op[j].label == 0 ) {
        if ( err ) {
            fprintf(err,"%sundefined option.\n",emsg);
            errline(i,1,err);
        }
        errcnt++;
    } else if ( op[j].arg == NULL ) {
        /* Ignore this option */
    } else if ( op[j].type == OPT_FLAG ) {
        *((int*)op[j].arg) = v;
    } else if ( op[j].type == OPT_FFLAG ) {
        (*(void(*)(int))(op[j].arg))(v);
    } else if ( op[j].type == OPT_FSTR ) {
        (*(void(*)(char *))(op[j].arg))(&argv[i][2]);
    } else {
        if ( err ) {
            fprintf(err,"%smissing argument on switch.\n",emsg);
            errline(i,1,err);
        }
        errcnt++;
    }
    return errcnt;
}

/*
** Process a command line switch which has an argument.
*/
static
int             handleswitch (
    LEMON_T         *pLem,
    int             i,
    FILE            *err
)
{
    int             lv = 0;
    double          dv = 0.0;
    char            *sv = 0;
    char            *end;
    char            *cp;
    int             j;
    int             errcnt = 0;
    
    cp = strchr(argv[i],'=');
    assert( cp != 0 );
    *cp = 0;
    for (j=0; op[j].label; j++) {
        if (strcmp(argv[i],op[j].label) == 0)
            break;
    }
    *cp = '=';
    if (op[j].label == 0) {
        if (err) {
            fprintf(err,"%sundefined option.\n",emsg);
            errline(i,0,err);
        }
        errcnt++;
    } else {
        cp++;
        switch (op[j].type) {
            case OPT_FLAG:
            case OPT_FFLAG:
                if( err ){
                    fprintf(err,"%soption requires an argument.\n",emsg);
                    errline(i,0,err);
                }
                errcnt++;
                break;
            case OPT_DBL:
            case OPT_FDBL:
                dv = strtod(cp, &end);
                if( *end ){
                    if( err ){
                        fprintf(err,
                                "%sillegal character in floating-point argument.\n",emsg);
                        errline(i,(int)((char*)end-(char*)argv[i]),err);
                    }
                    errcnt++;
                }
                break;
            case OPT_INT:
            case OPT_FINT:
                lv = (int)strtol(cp,&end,0);
                if( *end ){
                    if( err ){
                        fprintf(err,"%sillegal character in integer argument.\n",emsg);
                        errline(i,(int)((char*)end-(char*)argv[i]),err);
                    }
                    errcnt++;
                }
                break;
            case OPT_STR:
            case OPT_FSTR:
                sv = cp;
                break;
        }
        switch( op[j].type ){
            case OPT_FLAG:
            case OPT_FFLAG:
                break;
            case OPT_DBL:
                *(double*)(op[j].arg) = dv;
                break;
            case OPT_FDBL:
                (*(void(*)(double))(op[j].arg))(dv);
                break;
            case OPT_INT:
                *(int*)(op[j].arg) = lv;
                break;
            case OPT_FINT:
                (*(void(*)(int))(op[j].arg))((int)lv);
                break;
            case OPT_STR:
                *(char**)(op[j].arg) = sv;
                break;
            case OPT_FSTR:
                (*(void(*)(char *))(op[j].arg))(sv);
                break;
        }
    }
    return errcnt;
}



int             OptInit (
    LEMON_T         *pLem,
    char            **a,
    OPTIONS_T       *o,
    FILE            *err
)
{
    int             errcnt = 0;
    
    argv = a;
    op = o;
    errstream = err;
    if (argv && *argv && op) {
        int             i;
        for (i=1; argv[i]; i++) {
            if ((argv[i][0] == '+') || (argv[i][0] == '-' )){
                errcnt += handleflags(pLem, i, err);
            }else if (strchr(argv[i], '=')){
                errcnt += handleswitch(pLem, i, err);
            }
        }
  }
  if (errcnt > 0) {
    fprintf(err,"Valid command line options for \"%s\" are:\n",*a);
    OptPrint();
    exit(1);
  }
  return 0;
}


int             OptNArgs (
    void
)
{
    int             cnt = 0;
    int             dashdash = 0;
    int             i;

    if ((argv != 0) && (argv[0] != NULL)) {
        for (i=1; argv[i]; i++) {
            if (dashdash || !ISOPT(argv[i]) )
                cnt++;
            if (strcmp(argv[i],"--") == 0)
                dashdash = 1;
        }
    }
    return cnt;
}


char *OptArg(int n)
{
  int i;
  i = argindex(n);
  return i>=0 ? argv[i] : 0;
}


void OptErr(int n)
{
  int i;
  i = argindex(n);
  if( i>=0 ) errline(i,0,errstream);
}


void OptPrint(void){
  int i;
  int max, len;
  max = 0;
  for(i=0; op[i].label; i++){
    len = lemon_Strlen(op[i].label) + 1;
    switch( op[i].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        break;
      case OPT_INT:
      case OPT_FINT:
        len += 9;       /* length of "<integer>" */
        break;
      case OPT_DBL:
      case OPT_FDBL:
        len += 6;       /* length of "<real>" */
        break;
      case OPT_STR:
      case OPT_FSTR:
        len += 8;       /* length of "<string>" */
        break;
    }
    if( len>max ) max = len;
  }
  for(i=0; op[i].label; i++){
    switch( op[i].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        fprintf(errstream,"  -%-*s  %s\n",max,op[i].label,op[i].message);
        break;
      case OPT_INT:
      case OPT_FINT:
        fprintf(errstream,"  -%s<integer>%*s  %s\n",op[i].label,
          (int)(max-lemon_Strlen(op[i].label)-9),"",op[i].message);
        break;
      case OPT_DBL:
      case OPT_FDBL:
        fprintf(errstream,"  -%s<real>%*s  %s\n",op[i].label,
          (int)(max-lemon_Strlen(op[i].label)-6),"",op[i].message);
        break;
      case OPT_STR:
      case OPT_FSTR:
        fprintf(errstream,"  -%s<string>%*s  %s\n",op[i].label,
          (int)(max-lemon_Strlen(op[i].label)-8),"",op[i].message);
        break;
    }
  }
}

