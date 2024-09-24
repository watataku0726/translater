%skeleton "lalr1.cc"
%defines
%code requires{
#ifdef _MSC_VER
#pragma warning(disable: 4800)
#pragma warning(disable: 4276)
#endif 

#include <string>
#include "Node.h"
class Option;

}
%parse-param    { Option& driver }
%lex-param      { Option& driver }  
%locations
%expect 1
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.GetFilename();
};

%define parse.error verbose

%union {
    int             ival;
    std::string    *sval

    OptStateList   *states;
    OptDeclList    *decls;
    OptStatement   *statement;
    OptDeclaration *declaration;
    CArgs          *args;
    CValueNode     *value;
    CNode          *expr;
    CAssign        *assign;
    CStateBlock    *block;
}
%code {
#include "Option.h"
}

%token          END_OF_FILE    0"end of file"
%token <ival>   TK_IVAL         "ival"
%token <sval>   TK_IDENTIFIER   "identifier"
%token          TK_LOGOR        "||"
%token          TK_LOGAND       "&&"
%token          TK_EQ           "=="
%token          TK_NE           "!="
%token          TK_GE           ">="
%token          TK_LE           "<="
%token          TK_ADD_ASSIGN   "+="
%token          TK_SUB_ASSIGN   "-="

%token          TK_IF           "if"
%token          TK_ELSE         "else"
%token          TK_WHILE        "while"
%token          TK_DEF         "def"
%token          TK_LET          "let"
%token          TK_REGISTER     "Register"
%token          TK_INSTRUCTION  "Instruction"
%token          TK_LOCAL        "local"
%token          TK_LOAD         "load"
%token          TK_STORE        "store"

%type <expr>        expr
%type <value>       value
%type <assign>      assign
%type <decls>       decls decl_list
%type <states>      states state_list
%type <block>       block
%type <args>        args
%type <statement>   statement
%type <declaration> declaration

%destructor { delete $$; }  "identifier"

%destructor { delete $$; } decls decl_list
%destructor { delete $$; } states state_list
%destructor { delete $$; } args
%destructor { delete $$; } block
%destructor { delete $$; } assign
%destructor { delete $$; } statement
%destructor { delete $$; } value
%destructor { delete $$; } expr
%destructor { delete $$; } declaration

%left "||";
%left "&&";
%nonassoc "==" "!=" '>' '<' ">=" "<=";
%%
%start unit;

unit                : define_or_state ';'
                    | unit define_or_state
                    ;

define_or_state     : error ';'
                    | "def" "identifier" ':' "Register" ';'         { driver.DefineRegister(@2, $2); }
                    | "def" "identifier" ':' "Instruction" block    { driver.DefineInstruction(@2, $2, $5)}
                    ;

block               : '{' decl_list state_list '}'                  { $$ = new OptBlock($2, $3); }
                    ;

decl_list           :                                               { $$ = nullptr; }
                    | decls                                         { $$ = $1; }
                    ;

state_list          :                                               { $$ = nullptr; }
                    | states                                        { $$ = $1; }
                    ;

decls               : declaration                                   { $$ = new OptDecList($1); } 
                    | decls declaration                             { $$ = $1->Add($2); }
                    ;

declaration         : "def" "identifier" ';' "local" ';'            { $$ = new OptDecl($2); }
                    ;

states              : statement                                     { $$ = new OptStateList($1)}
                    | states statement                              { $$ = $1->Add($2); }
                    ;

statement           : ';'                                               { $$ = new OptNopStatement(@1); }
                    | assign ';'                                        { $$ = new OptLetStatement(@1, $1); }
                    | "identifier" '(' args ')' ';'                     { $$ = new OptFunctionStatement(@1, $1, $3); }   
                    | "identifier" '(' ')' ';'                          { $$ = new OptFunctionStatement(@1, $1, nullptr); }
                    | "if" '(' expr ')' statement                       { $$ = new OptIfStatement(@1, $3, $5); }  
                    | "if" '(' expr ')' statement "else" statement      { $$ = new OptIfStatement(@1, $3, $5, $7); }
                    | "while" '(' expr ')' statement                    { $$ = new OptWhileStatement(@1, $3, $5); }
                    | "load" '<' "identifier" ',' "identifier" '>' ';'  { $$ = new OptLoadStatement(@1, $3, $5); }
                    | "store" '<' "identifier" ',' "identifier" '>' ';' { $$ = new OptStoreStatement(@1, $3, $5); }
                    | block                                             { $$ = new OptBlockStatement(@1, $1); }
                    ;

assign              : "let" value '=' expr                          { $$ = new OptLet(@1, '=', $2, $4); }
                    | "let" value "+=" expr                         { $$ = new OptLet(@1, '+', $2, $4); }
                    | "let" value "-=" expr                         { $$ = new OptLet(@1, '-', $2, $4); }
                    ;

expr                : expr "&&" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_LOGAND, $1, $3); }
                    | expr "||" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_LOGOR, $1, $3); }
                    | expr "==" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_EQ, $1, $3); }
                    | expr "!=" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_NE, $1, $3); }
                    | expr ">=" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_GE, $1, $3); }
                    | expr "<=" expr            { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_LE, $1, $3); }
                    | expr '>' expr             { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_GT, $1, $3); }
                    | expr '<' expr             { $$ = new OptNode::MakeNode(driver, @2, OPCODE::OP_LT, $1, $3); }
                    | '(' expr ')'              { $$ = $2; }
                    | value                     { $$ = $1; }
                    | "ival"                    { $$ = new CNode(@1, OPCODE::OP_CONST, $1); }
                    | "identifier" '(' args ')' {$$ = new CFunctionNode(@1, $1, $3); }
                    | "identifier" '(' ')'      {$$ = new CFunctionNode(@1, $1, nullptr); }
                    ;

value               : "identifier"              { $$ = new CValueNode(@1, $1); }
                    ;

args                : expr                      { $$ = new CArgs($1); }
                    | args ',' expr             { $$ = $1->Add($3); }
                    ;

%%
void yy::parser::error(const yy::parser::location_type& l, const std::string& m) {
    driver.error(l, m);
}