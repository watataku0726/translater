// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 39 "parser.y"

#include "Option.h"

#line 50 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cc"

  /// Build a parser object.
  parser::parser (Option& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.kind ())
    {
      case symbol_kind::S_TK_IDENTIFIER: // "identifier"
#line 81 "parser.y"
                    { delete (yysym.value.sval); }
#line 354 "parser.cc"
        break;

      case symbol_kind::S_inst_block: // inst_block
#line 86 "parser.y"
                    { delete (yysym.value.block); }
#line 360 "parser.cc"
        break;

      case symbol_kind::S_block: // block
#line 86 "parser.y"
                    { delete (yysym.value.block); }
#line 366 "parser.cc"
        break;

      case symbol_kind::S_decl_list: // decl_list
#line 83 "parser.y"
                    { delete (yysym.value.decls); }
#line 372 "parser.cc"
        break;

      case symbol_kind::S_state_list: // state_list
#line 84 "parser.y"
                    { delete (yysym.value.states); }
#line 378 "parser.cc"
        break;

      case symbol_kind::S_decls: // decls
#line 83 "parser.y"
                    { delete (yysym.value.decls); }
#line 384 "parser.cc"
        break;

      case symbol_kind::S_declaration: // declaration
#line 91 "parser.y"
                    { delete (yysym.value.declaration); }
#line 390 "parser.cc"
        break;

      case symbol_kind::S_states: // states
#line 84 "parser.y"
                    { delete (yysym.value.states); }
#line 396 "parser.cc"
        break;

      case symbol_kind::S_statement: // statement
#line 88 "parser.y"
                    { delete (yysym.value.statement); }
#line 402 "parser.cc"
        break;

      case symbol_kind::S_assign: // assign
#line 87 "parser.y"
                    { delete (yysym.value.assign); }
#line 408 "parser.cc"
        break;

      case symbol_kind::S_expr: // expr
#line 90 "parser.y"
                    { delete (yysym.value.expr); }
#line 414 "parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 89 "parser.y"
                    { delete (yysym.value.value); }
#line 420 "parser.cc"
        break;

      case symbol_kind::S_args: // args
#line 85 "parser.y"
                    { delete (yysym.value.args); }
#line 426 "parser.cc"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 19 "parser.y"
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.GetFileName();
}

#line 568 "parser.cc"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 5: // define_or_state: "def" "identifier" ':' "Register" ';'
#line 105 "parser.y"
                                                                        { driver.DefineRegister(yystack_[3].location, (yystack_[3].value.sval)); }
#line 706 "parser.cc"
    break;

  case 6: // define_or_state: "def" "identifier" ':' "Instruction" inst_block
#line 106 "parser.y"
                                                                        { driver.DefineInstruction(yystack_[3].location, (yystack_[3].value.sval), (yystack_[0].value.block)); }
#line 712 "parser.cc"
    break;

  case 7: // define_or_state: "let" "projectName" '=' "identifier" ';'
#line 107 "parser.y"
                                                                        { driver.SetProjectName(yystack_[3].location, (yystack_[1].value.sval)); }
#line 718 "parser.cc"
    break;

  case 8: // inst_block: '{' decl_list state_list '}'
#line 110 "parser.y"
                                                                    { (yylhs.value.block) = new OptStateBlock((yystack_[2].value.decls), (yystack_[1].value.states)); }
#line 724 "parser.cc"
    break;

  case 9: // block: '{' state_list '}'
#line 113 "parser.y"
                                                                    { (yylhs.value.block) = new OptStateBlock(nullptr, (yystack_[1].value.states)); }
#line 730 "parser.cc"
    break;

  case 10: // decl_list: %empty
#line 115 "parser.y"
                                                                    { (yylhs.value.decls) = nullptr; }
#line 736 "parser.cc"
    break;

  case 11: // decl_list: decls
#line 116 "parser.y"
                                                                    { (yylhs.value.decls) = (yystack_[0].value.decls); }
#line 742 "parser.cc"
    break;

  case 12: // state_list: %empty
#line 119 "parser.y"
                                                                    { (yylhs.value.states) = nullptr; }
#line 748 "parser.cc"
    break;

  case 13: // state_list: states
#line 120 "parser.y"
                                                                    { (yylhs.value.states) = (yystack_[0].value.states); }
#line 754 "parser.cc"
    break;

  case 14: // decls: declaration
#line 123 "parser.y"
                                                                    { (yylhs.value.decls) = new OptDeclList((yystack_[0].value.declaration)); }
#line 760 "parser.cc"
    break;

  case 15: // decls: decls declaration
#line 124 "parser.y"
                                                                    { (yylhs.value.decls) = (yystack_[1].value.decls)->Add((yystack_[0].value.declaration)); }
#line 766 "parser.cc"
    break;

  case 16: // declaration: "def" value ':' "local" ';'
#line 127 "parser.y"
                                                                    { (yylhs.value.declaration) = new OptDecl((yystack_[3].value.value), OptDecl::Kind::LOCAL); }
#line 772 "parser.cc"
    break;

  case 17: // declaration: "def" value ':' "rd" ';'
#line 128 "parser.y"
                                                                    { (yylhs.value.declaration) = new OptDecl((yystack_[3].value.value), OptDecl::Kind::RD);}
#line 778 "parser.cc"
    break;

  case 18: // declaration: "def" value ':' "rs1" ';'
#line 129 "parser.y"
                                                                    { (yylhs.value.declaration) = new OptDecl((yystack_[3].value.value), OptDecl::Kind::RS1);}
#line 784 "parser.cc"
    break;

  case 19: // declaration: "def" value ':' "rs2" ';'
#line 130 "parser.y"
                                                                    { (yylhs.value.declaration) = new OptDecl((yystack_[3].value.value), OptDecl::Kind::RS2);}
#line 790 "parser.cc"
    break;

  case 20: // states: statement
#line 133 "parser.y"
                                                                    { (yylhs.value.states) = new OptStateList((yystack_[0].value.statement));}
#line 796 "parser.cc"
    break;

  case 21: // states: states statement
#line 134 "parser.y"
                                                                    { (yylhs.value.states) = (yystack_[1].value.states)->Add((yystack_[0].value.statement)); }
#line 802 "parser.cc"
    break;

  case 22: // statement: ';'
#line 137 "parser.y"
                                                                        { (yylhs.value.statement) = new OptNopStatement(yystack_[0].location); }
#line 808 "parser.cc"
    break;

  case 23: // statement: assign ';'
#line 138 "parser.y"
                                                                        { (yylhs.value.statement) = new OptLetStatement(yystack_[1].location, (yystack_[1].value.assign)); }
#line 814 "parser.cc"
    break;

  case 24: // statement: "identifier" '(' args ')' ';'
#line 139 "parser.y"
                                                                        { (yylhs.value.statement) = new OptFunctionStatement(yystack_[4].location, (yystack_[4].value.sval), (yystack_[2].value.args)); }
#line 820 "parser.cc"
    break;

  case 25: // statement: "identifier" '(' ')' ';'
#line 140 "parser.y"
                                                                        { (yylhs.value.statement) = new OptFunctionStatement(yystack_[3].location, (yystack_[3].value.sval), nullptr); }
#line 826 "parser.cc"
    break;

  case 26: // statement: "if" '(' expr ')' statement
#line 141 "parser.y"
                                                                        { (yylhs.value.statement) = new OptIfStatement(yystack_[4].location, (yystack_[2].value.expr), (yystack_[0].value.statement)); }
#line 832 "parser.cc"
    break;

  case 27: // statement: "if" '(' expr ')' statement "else" statement
#line 142 "parser.y"
                                                                        { (yylhs.value.statement) = new OptIfStatement(yystack_[6].location, (yystack_[4].value.expr), (yystack_[2].value.statement), (yystack_[0].value.statement)); }
#line 838 "parser.cc"
    break;

  case 28: // statement: "while" '(' expr ')' statement
#line 143 "parser.y"
                                                                        { (yylhs.value.statement) = new OptWhileStatement(yystack_[4].location, (yystack_[2].value.expr), (yystack_[0].value.statement)); }
#line 844 "parser.cc"
    break;

  case 29: // statement: "load" value "<=" '<' value '>' ';'
#line 144 "parser.y"
                                                                        { (yylhs.value.statement) = new OptLoadStatement(yystack_[6].location, (yystack_[5].value.value), (yystack_[2].value.value)); }
#line 850 "parser.cc"
    break;

  case 30: // statement: "store" '<' value '>' "<=" value ';'
#line 145 "parser.y"
                                                                        { (yylhs.value.statement) = new OptStoreStatement(yystack_[6].location, (yystack_[1].value.value), (yystack_[4].value.value)); }
#line 856 "parser.cc"
    break;

  case 31: // statement: block
#line 146 "parser.y"
                                                                        { (yylhs.value.statement) = new OptBlockStatement(yystack_[0].location, (yystack_[0].value.block)); }
#line 862 "parser.cc"
    break;

  case 32: // assign: "let" value '=' expr
#line 149 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '=', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 868 "parser.cc"
    break;

  case 33: // assign: "let" value "+=" expr
#line 150 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '+', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 874 "parser.cc"
    break;

  case 34: // assign: "let" value "-=" expr
#line 151 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '-', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 880 "parser.cc"
    break;

  case 35: // expr: expr "&&" expr
#line 154 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LOGAND, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 886 "parser.cc"
    break;

  case 36: // expr: expr "||" expr
#line 155 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LOGOR, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 892 "parser.cc"
    break;

  case 37: // expr: expr "==" expr
#line 156 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 898 "parser.cc"
    break;

  case 38: // expr: expr "!=" expr
#line 157 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_NE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 904 "parser.cc"
    break;

  case 39: // expr: expr ">=" expr
#line 158 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_GE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 910 "parser.cc"
    break;

  case 40: // expr: expr "<=" expr
#line 159 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 916 "parser.cc"
    break;

  case 41: // expr: expr '>' expr
#line 160 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_GT, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 922 "parser.cc"
    break;

  case 42: // expr: expr '<' expr
#line 161 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LT, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 928 "parser.cc"
    break;

  case 43: // expr: '-' expr
#line 162 "parser.y"
                                                { (yylhs.value.expr) =  OptNode::MakeNode(driver, yystack_[0].location, OPCODE::OP_NEG, (yystack_[0].value.expr)); }
#line 934 "parser.cc"
    break;

  case 44: // expr: '(' expr ')'
#line 163 "parser.y"
                                                { (yylhs.value.expr) = (yystack_[1].value.expr); }
#line 940 "parser.cc"
    break;

  case 45: // expr: value
#line 164 "parser.y"
                                                { (yylhs.value.expr) = (yystack_[0].value.value); }
#line 946 "parser.cc"
    break;

  case 46: // expr: "ival"
#line 165 "parser.y"
                                                { (yylhs.value.expr) = new OptNode(yystack_[0].location, OPCODE::OP_CONST, (yystack_[0].value.ival)); }
#line 952 "parser.cc"
    break;

  case 47: // expr: "identifier" '(' args ')'
#line 166 "parser.y"
                                                { (yylhs.value.expr) = new OptFunctionNode(yystack_[3].location, (yystack_[3].value.sval), (yystack_[1].value.args)); }
#line 958 "parser.cc"
    break;

  case 48: // expr: "identifier" '(' ')'
#line 167 "parser.y"
                                                { (yylhs.value.expr) = new OptFunctionNode(yystack_[2].location, (yystack_[2].value.sval), nullptr); }
#line 964 "parser.cc"
    break;

  case 49: // value: "identifier"
#line 170 "parser.y"
                                                { (yylhs.value.value) = new OptValueNode(yystack_[0].location, (yystack_[0].value.sval)); }
#line 970 "parser.cc"
    break;

  case 50: // args: expr
#line 173 "parser.y"
                                                { (yylhs.value.args) = new OptArgs((yystack_[0].value.expr)); }
#line 976 "parser.cc"
    break;

  case 51: // args: args ',' expr
#line 174 "parser.y"
                                                { (yylhs.value.args) = (yystack_[2].value.args)->Add((yystack_[0].value.expr)); }
#line 982 "parser.cc"
    break;


#line 986 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -39;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       7,   -14,    21,    29,   108,   -39,   -39,     6,    43,   -39,
     -39,    12,    49,    46,    52,    76,   -39,    72,   -39,   -39,
      89,    90,    72,   -39,   -39,    79,    78,    86,    87,    89,
      89,    98,   -39,    90,   -39,   102,    90,   -39,   109,   -39,
      58,    -1,    14,    14,    45,   127,    89,   104,   -39,   -39,
     -39,   110,   111,   112,   113,   -39,   114,    14,   115,    14,
     123,   -39,   -16,    53,    59,    14,    14,    14,   116,   119,
     -39,   -39,   -39,   -39,   -39,     3,    91,   -39,   -39,    14,
      14,    14,    14,    14,    14,    14,    14,   117,    14,    90,
      90,   123,   123,   123,    89,   138,   -39,    66,   -39,     5,
      63,   107,   107,   107,   107,   107,   107,   -39,   123,   139,
     -39,   125,    89,   -39,    90,   124,   126,   -39,   -39,   -39
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     4,     0,     0,     1,
       3,     0,     0,     0,     0,     0,     5,    10,     6,     7,
       0,    12,    11,    14,    49,     0,     0,     0,     0,     0,
       0,     0,    22,    12,    31,     0,    13,    20,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     8,    21,
      23,     0,     0,     0,     0,    46,    49,     0,     0,     0,
      50,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       9,    16,    17,    18,    19,     0,     0,    25,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,    34,    32,     0,     0,    48,     0,    44,    36,
      35,    37,    38,    39,    40,    41,    42,    24,    51,    26,
      28,     0,     0,    47,     0,     0,     0,    27,    29,    30
  };

  const short
  parser::yypgoto_[] =
  {
     -39,   -39,   151,   -39,   -39,   -39,   128,   -39,   135,   -39,
     -35,   -39,   -38,   -20,    83
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     4,     5,    18,    34,    21,    35,    22,    23,    36,
      37,    38,    60,    61,    62
  };

  const signed char
  parser::yytable_[] =
  {
      25,    49,    55,    56,    63,    64,    55,    56,     1,    44,
      45,    80,    81,    82,    83,    84,     6,    55,    56,    76,
      87,    78,    88,     2,     3,     7,    69,    91,    92,    93,
      13,    14,    85,    86,    57,    58,    59,    11,    57,    96,
      59,    99,   100,   101,   102,   103,   104,   105,   106,    57,
     108,    59,     8,    15,   109,   110,    65,    66,    79,    80,
      81,    82,    83,    84,    79,    80,    81,    82,    83,    84,
      81,    82,    83,    84,   111,    12,    16,    67,    51,   117,
      85,    86,    52,    53,    54,    17,    85,    86,    20,    89,
      85,    86,   116,    24,    26,    90,    79,    80,    81,    82,
      83,    84,   113,    27,    88,    28,    19,    29,     9,     1,
      40,    30,    31,    41,    -1,    -1,    -1,    -1,    85,    86,
      32,    42,    43,    33,     2,     3,    46,    98,    79,    80,
      81,    82,    83,    84,    -1,    -1,    48,    68,    70,    50,
      71,    72,    73,    74,    94,    77,    95,   107,   112,    75,
      85,    86,   115,   114,   118,    10,   119,    39,    97,     0,
       0,    47
  };

  const signed char
  parser::yycheck_[] =
  {
      20,    36,     3,     4,    42,    43,     3,     4,     1,    29,
      30,     6,     7,     8,     9,    10,    30,     3,     4,    57,
      36,    59,    38,    16,    17,     4,    46,    65,    66,    67,
      18,    19,    27,    28,    35,    36,    37,    31,    35,    36,
      37,    79,    80,    81,    82,    83,    84,    85,    86,    35,
      88,    37,    23,     4,    89,    90,    11,    12,     5,     6,
       7,     8,     9,    10,     5,     6,     7,     8,     9,    10,
       7,     8,     9,    10,    94,    32,    30,    32,    20,   114,
      27,    28,    24,    25,    26,    33,    27,    28,    16,    36,
      27,    28,   112,     4,     4,    36,     5,     6,     7,     8,
       9,    10,    36,    13,    38,    15,    30,    17,     0,     1,
      31,    21,    22,    35,     7,     8,     9,    10,    27,    28,
      30,    35,    35,    33,    16,    17,    28,    36,     5,     6,
       7,     8,     9,    10,    27,    28,    34,    10,    34,    30,
      30,    30,    30,    30,    28,    30,    27,    30,    10,    35,
      27,    28,    27,    14,    30,     4,    30,    22,    75,    -1,
      -1,    33
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,    16,    17,    40,    41,    30,     4,    23,     0,
      41,    31,    32,    18,    19,     4,    30,    33,    42,    30,
      16,    44,    46,    47,     4,    52,     4,    13,    15,    17,
      21,    22,    30,    33,    43,    45,    48,    49,    50,    47,
      31,    35,    35,    35,    52,    52,    28,    45,    34,    49,
      30,    20,    24,    25,    26,     3,     4,    35,    36,    37,
      51,    52,    53,    51,    51,    11,    12,    32,    10,    52,
      34,    30,    30,    30,    30,    35,    51,    30,    51,     5,
       6,     7,     8,     9,    10,    27,    28,    36,    38,    36,
      36,    51,    51,    51,    28,    27,    36,    53,    36,    51,
      51,    51,    51,    51,    51,    51,    51,    30,    51,    49,
      49,    52,    10,    36,    14,    27,    52,    49,    30,    30
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    39,    40,    40,    41,    41,    41,    41,    42,    43,
      44,    44,    45,    45,    46,    46,    47,    47,    47,    47,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      53,    53
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     2,     5,     5,     5,     4,     3,
       0,     1,     0,     1,     1,     2,     5,     5,     5,     5,
       1,     2,     1,     2,     5,     4,     5,     7,     5,     7,
       7,     1,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     4,     3,     1,
       1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"ival\"",
  "\"identifier\"", "\"||\"", "\"&&\"", "\"==\"", "\"!=\"", "\">=\"",
  "\"<=\"", "\"+=\"", "\"-=\"", "\"if\"", "\"else\"", "\"while\"",
  "\"def\"", "\"let\"", "\"Register\"", "\"Instruction\"", "\"local\"",
  "\"load\"", "\"store\"", "\"projectName\"", "\"rd\"", "\"rs1\"",
  "\"rs2\"", "'>'", "'<'", "NEG", "';'", "':'", "'='", "'{'", "'}'", "'('",
  "')'", "'-'", "','", "$accept", "unit", "define_or_state", "inst_block",
  "block", "decl_list", "state_list", "decls", "declaration", "states",
  "statement", "assign", "expr", "value", "args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   100,   100,   101,   104,   105,   106,   107,   110,   113,
     115,   116,   119,   120,   123,   124,   127,   128,   129,   130,
     133,   134,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   149,   150,   151,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   170,
     173,   174
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,     2,     2,    38,    37,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    31,    30,
      28,    32,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    29
    };
    // Last valid token kind.
    const int code_max = 282;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1583 "parser.cc"

#line 177 "parser.y"

void yy::parser::error(const yy::parser::location_type& l, const std::string& m) {
    driver.error(l, m);
}
