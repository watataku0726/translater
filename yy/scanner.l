%{
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <string>
#include "Option.h"
#include "parser.hh"

#if defined(_MSC_VER)
#pragma warning(disable:4018)
#pragma warning(disable:4102)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#endif 

#undef yywrap
#define yywrap() 1

#define yyterminate() return token::END_OF_FILE
%}

%option noyywrap nounput batch
%option never-interactive
%option noyy_scan_buffer
%option noyy_scan_bytes
%option noyy_scan_string
%option 8bit
%option nounistd

id      [a-zA-Z_][a-zA-Z_0-9]*
int     [1-9][0-9]*
blank   [ \t]

%x C_COMMENT
%x CPP_COMMENT

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}
%%
%{
    typedef yy::parser::token token;

    yylloc->step();

    std::string string_buffer;
%}
<INITIAL>{
    \n              { yylloc->lines(); }
    "^#"            { yylloc->step(); BEGIN(CPP_COMMENT); }
    "//"            { yylloc->step(); BEGIN(CPP_COMMENT); }
    "/*"            { yylloc->step(); BEGIN(C_COMMENT); }

    "if"            return token::TK_IF;
    "else"          return token::TK_ELSE;
    "while"         return token::TK_WHILE;

    "load"          return token::TK_LOAD;
    "store"         return token::TK_STORE;
    "Instruction"   return token::TK_INSTRUCTION;
    "Register"      return token::TK_REGISTER;
    "local"         return token::TK_LOCAL;
    "def"           return token::TK_DEF;
    "let"           return token::TK_LET;
    "projectName"   return token::TK_PROJECTNAME;
    "rd"            return token::TK_RD;
    "rs1"           return token::TK_RS1;
    "rs2"           return token::TK_RS2;

    \\\n            yylloc->lines();

    [=(){}<>,:;]      return yy::parser::token_type(yytext[0]);

    "&&"            return token::TK_LOGAND;
    "||"            return token::TK_LOGOR;
    "=="            return token::TK_EQ;
    "!="            return token::TK_NE;
    ">="            return token::TK_GE;
    "<="            return token::TK_LE;

    "+="            return token::TK_ADD_ASSIGN;
    "-="            return token::TK_SUB_ASSIGN;

    {blank}+        yylloc->step();
    {int}           {
                        errno = 0;
                        long n = strtol(yytext, nullptr, 10);
                        if (n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                            driver.error(*yylloc, "Out of Integier Range");
                        yylval->ival = n;
                        return token::TK_IVAL;
                    }
    "0"             {
                        yylval->ival = 0;
                        return token::TK_IVAL;
                    }
    {id}            {
                        yylval->sval = new std::string(yytext);
                        return token::TK_IDENTIFIER;
                    }
    .               driver.error(*yylloc, "This charactor cannot be used in identifiers.");
}
<CPP_COMMENT>{
    [^\n]*          {
                        yylloc->lines();
                        yylloc->step();
                        BEGIN(INITIAL);
                    }
}
<C_COMMENT>{
    [^*\n]*
    [^*\n]*\n       { yylloc->lines(); }
    "*"+[^*/\n]*    
    "*"+[^*/\n]*\n  {yylloc->lines(); }
    <<EOF>>         driver.error(*yylloc, "File ended in the middle of comment.");
    "*"+"/"         BEGIN(INITIAL);
}
%%

bool Option::scan_begin() {
    if((yyin = fopen(mFileName.c_str(), "r")) == 0) {
        error("Failed to open file : " + mFileName);
        return false;
    } 
    return true;  
}

void Option::scan_end() {
    fclose(yyin);
    yylex_destroy();
}