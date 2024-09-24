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
#line 76 "parser.y"
                    { delete (yysym.value.sval); }
#line 354 "parser.cc"
        break;

      case symbol_kind::S_block: // block
#line 81 "parser.y"
                    { delete (yysym.value.block); }
#line 360 "parser.cc"
        break;

      case symbol_kind::S_decl_list: // decl_list
#line 78 "parser.y"
                    { delete (yysym.value.decls); }
#line 366 "parser.cc"
        break;

      case symbol_kind::S_state_list: // state_list
#line 79 "parser.y"
                    { delete (yysym.value.states); }
#line 372 "parser.cc"
        break;

      case symbol_kind::S_decls: // decls
#line 78 "parser.y"
                    { delete (yysym.value.decls); }
#line 378 "parser.cc"
        break;

      case symbol_kind::S_declaration: // declaration
#line 86 "parser.y"
                    { delete (yysym.value.declaration); }
#line 384 "parser.cc"
        break;

      case symbol_kind::S_states: // states
#line 79 "parser.y"
                    { delete (yysym.value.states); }
#line 390 "parser.cc"
        break;

      case symbol_kind::S_statement: // statement
#line 83 "parser.y"
                    { delete (yysym.value.statement); }
#line 396 "parser.cc"
        break;

      case symbol_kind::S_assign: // assign
#line 82 "parser.y"
                    { delete (yysym.value.assign); }
#line 402 "parser.cc"
        break;

      case symbol_kind::S_expr: // expr
#line 85 "parser.y"
                    { delete (yysym.value.expr); }
#line 408 "parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 84 "parser.y"
                    { delete (yysym.value.value); }
#line 414 "parser.cc"
        break;

      case symbol_kind::S_args: // args
#line 80 "parser.y"
                    { delete (yysym.value.args); }
#line 420 "parser.cc"
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
    yyla.location.begin.filename = yyla.location.end.filename = &driver.GetFilename();
}

#line 562 "parser.cc"


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
#line 99 "parser.y"
                                                                    { driver.DefineRegister(yystack_[3].location, (yystack_[3].value.sval)); }
#line 700 "parser.cc"
    break;

  case 6: // define_or_state: "def" "identifier" ':' "Instruction" block
#line 100 "parser.y"
                                                                    { driver.DefineInstruction(yystack_[3].location, (yystack_[3].value.sval), (yystack_[0].value.block))}
#line 706 "parser.cc"
    break;

  case 7: // block: '{' decl_list state_list '}'
#line 103 "parser.y"
                                                                    { (yylhs.value.block) = new OptBlock((yystack_[2].value.decls), (yystack_[1].value.states)); }
#line 712 "parser.cc"
    break;

  case 8: // decl_list: %empty
#line 106 "parser.y"
                                                                    { (yylhs.value.decls) = nullptr; }
#line 718 "parser.cc"
    break;

  case 9: // decl_list: decls
#line 107 "parser.y"
                                                                    { (yylhs.value.decls) = (yystack_[0].value.decls); }
#line 724 "parser.cc"
    break;

  case 10: // state_list: %empty
#line 110 "parser.y"
                                                                    { (yylhs.value.states) = nullptr; }
#line 730 "parser.cc"
    break;

  case 11: // state_list: states
#line 111 "parser.y"
                                                                    { (yylhs.value.states) = (yystack_[0].value.states); }
#line 736 "parser.cc"
    break;

  case 12: // decls: declaration
#line 114 "parser.y"
                                                                    { (yylhs.value.decls) = new OptDecList((yystack_[0].value.declaration)); }
#line 742 "parser.cc"
    break;

  case 13: // decls: decls declaration
#line 115 "parser.y"
                                                                    { (yylhs.value.decls) = (yystack_[1].value.decls)->Add((yystack_[0].value.declaration)); }
#line 748 "parser.cc"
    break;

  case 14: // declaration: "def" "identifier" ';' "local" ';'
#line 118 "parser.y"
                                                                    { (yylhs.value.declaration) = new OptDecl((yystack_[3].value.sval)); }
#line 754 "parser.cc"
    break;

  case 15: // states: statement
#line 121 "parser.y"
                                                                    { (yylhs.value.states) = new OptStateList((yystack_[0].value.statement))}
#line 760 "parser.cc"
    break;

  case 16: // states: states statement
#line 122 "parser.y"
                                                                    { (yylhs.value.states) = (yystack_[1].value.states)->Add((yystack_[0].value.statement)); }
#line 766 "parser.cc"
    break;

  case 17: // statement: ';'
#line 125 "parser.y"
                                                                        { (yylhs.value.statement) = new OptNopStatement(yystack_[0].location); }
#line 772 "parser.cc"
    break;

  case 18: // statement: assign ';'
#line 126 "parser.y"
                                                                        { (yylhs.value.statement) = new OptLetStatement(yystack_[1].location, (yystack_[1].value.assign)); }
#line 778 "parser.cc"
    break;

  case 19: // statement: "identifier" '(' args ')' ';'
#line 127 "parser.y"
                                                                        { (yylhs.value.statement) = new OptFunctionStatement(yystack_[4].location, (yystack_[4].value.sval), (yystack_[2].value.args)); }
#line 784 "parser.cc"
    break;

  case 20: // statement: "identifier" '(' ')' ';'
#line 128 "parser.y"
                                                                        { (yylhs.value.statement) = new OptFunctionStatement(yystack_[3].location, (yystack_[3].value.sval), nullptr); }
#line 790 "parser.cc"
    break;

  case 21: // statement: "if" '(' expr ')' statement
#line 129 "parser.y"
                                                                        { (yylhs.value.statement) = new OptIfStatement(yystack_[4].location, (yystack_[2].value.expr), (yystack_[0].value.statement)); }
#line 796 "parser.cc"
    break;

  case 22: // statement: "if" '(' expr ')' statement "else" statement
#line 130 "parser.y"
                                                                        { (yylhs.value.statement) = new OptIfStatement(yystack_[6].location, (yystack_[4].value.expr), (yystack_[2].value.statement), (yystack_[0].value.statement)); }
#line 802 "parser.cc"
    break;

  case 23: // statement: "while" '(' expr ')' statement
#line 131 "parser.y"
                                                                        { (yylhs.value.statement) = new OptWhileStatement(yystack_[4].location, (yystack_[2].value.expr), (yystack_[0].value.statement)); }
#line 808 "parser.cc"
    break;

  case 24: // statement: "load" '<' "identifier" ',' "identifier" '>' ';'
#line 132 "parser.y"
                                                                        { (yylhs.value.statement) = new OptLoadStatement(yystack_[6].location, (yystack_[4].value.sval), (yystack_[2].value.sval)); }
#line 814 "parser.cc"
    break;

  case 25: // statement: "store" '<' "identifier" ',' "identifier" '>' ';'
#line 133 "parser.y"
                                                                        { (yylhs.value.statement) = new OptStoreStatement(yystack_[6].location, (yystack_[4].value.sval), (yystack_[2].value.sval)); }
#line 820 "parser.cc"
    break;

  case 26: // statement: block
#line 134 "parser.y"
                                                                        { (yylhs.value.statement) = new OptBlockStatement(yystack_[0].location, (yystack_[0].value.block)); }
#line 826 "parser.cc"
    break;

  case 27: // assign: "let" value '=' expr
#line 137 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '=', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 832 "parser.cc"
    break;

  case 28: // assign: "let" value "+=" expr
#line 138 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '+', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 838 "parser.cc"
    break;

  case 29: // assign: "let" value "-=" expr
#line 139 "parser.y"
                                                                    { (yylhs.value.assign) = new OptLet(yystack_[3].location, '-', (yystack_[2].value.value), (yystack_[0].value.expr)); }
#line 844 "parser.cc"
    break;

  case 30: // expr: expr "&&" expr
#line 142 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LOGAND, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 850 "parser.cc"
    break;

  case 31: // expr: expr "||" expr
#line 143 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LOGOR, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 856 "parser.cc"
    break;

  case 32: // expr: expr "==" expr
#line 144 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_EQ, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 862 "parser.cc"
    break;

  case 33: // expr: expr "!=" expr
#line 145 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_NE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 868 "parser.cc"
    break;

  case 34: // expr: expr ">=" expr
#line 146 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_GE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 874 "parser.cc"
    break;

  case 35: // expr: expr "<=" expr
#line 147 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LE, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 880 "parser.cc"
    break;

  case 36: // expr: expr '>' expr
#line 148 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_GT, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 886 "parser.cc"
    break;

  case 37: // expr: expr '<' expr
#line 149 "parser.y"
                                                { (yylhs.value.expr) = new OptNode::MakeNode(driver, yystack_[1].location, OPCODE::OP_LT, (yystack_[2].value.expr), (yystack_[0].value.expr)); }
#line 892 "parser.cc"
    break;

  case 38: // expr: '(' expr ')'
#line 150 "parser.y"
                                                { (yylhs.value.expr) = (yystack_[1].value.expr); }
#line 898 "parser.cc"
    break;

  case 39: // expr: value
#line 151 "parser.y"
                                                { (yylhs.value.expr) = (yystack_[0].value.value); }
#line 904 "parser.cc"
    break;

  case 40: // expr: "ival"
#line 152 "parser.y"
                                                { (yylhs.value.expr) = new CNode(yystack_[0].location, OPCODE::OP_CONST, (yystack_[0].value.ival)); }
#line 910 "parser.cc"
    break;

  case 41: // expr: "identifier" '(' args ')'
#line 153 "parser.y"
                                                {(yylhs.value.expr) = new CFunctionNode(yystack_[3].location, (yystack_[3].value.sval), (yystack_[1].value.args)); }
#line 916 "parser.cc"
    break;

  case 42: // expr: "identifier" '(' ')'
#line 154 "parser.y"
                                                {(yylhs.value.expr) = new CFunctionNode(yystack_[2].location, (yystack_[2].value.sval), nullptr); }
#line 922 "parser.cc"
    break;

  case 43: // value: "identifier"
#line 157 "parser.y"
                                                { (yylhs.value.value) = new CValueNode(yystack_[0].location, (yystack_[0].value.sval)); }
#line 928 "parser.cc"
    break;

  case 44: // args: expr
#line 160 "parser.y"
                                                { (yylhs.value.args) = new CArgs((yystack_[0].value.expr)); }
#line 934 "parser.cc"
    break;

  case 45: // args: args ',' expr
#line 161 "parser.y"
                                                { (yylhs.value.args) = (yystack_[2].value.args)->Add((yystack_[0].value.expr)); }
#line 940 "parser.cc"
    break;


#line 944 "parser.cc"

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


  const signed char parser::yypact_ninf_ = -36;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
       9,   -16,    24,     7,    14,   -36,    26,   -36,   -36,   -36,
     -13,    28,    39,   -36,    51,   -36,    64,    87,    51,   -36,
      45,    46,    57,    58,    70,    54,    65,   -36,   -36,    60,
      87,   -36,    67,   -36,    73,    11,     8,     8,   -36,    -8,
      86,    90,   -36,   -36,   -36,    71,   -36,    66,     8,    72,
     110,   -36,   -12,    41,    49,     8,     8,     8,    76,    79,
     -36,    13,    75,   -36,     8,     8,     8,     8,     8,     8,
       8,     8,    78,     8,    87,    87,   110,   110,   110,    97,
     102,   -36,    -4,   -36,   115,    53,   119,   119,   119,   119,
     119,   119,   -36,   110,    99,   -36,    88,   107,   -36,    87,
     106,   111,   -36,   -36,   -36
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     4,     0,     1,     3,     2,
       0,     0,     0,     5,     8,     6,     0,    10,     9,    12,
       0,     0,     0,     0,     0,     0,     0,    17,    26,     0,
      11,    15,     0,    13,     0,     0,     0,     0,    43,     0,
       0,     0,     7,    16,    18,     0,    40,    43,     0,     0,
      44,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      14,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    27,     0,
       0,    42,     0,    38,    31,    30,    32,    33,    34,    35,
      36,    37,    19,    45,    21,    23,     0,     0,    41,     0,
       0,     0,    22,    24,    25
  };

  const short
  parser::yypgoto_[] =
  {
     -36,   -36,   129,   123,   -36,   -36,   -36,   122,   -36,   -30,
     -36,   -35,   113,    80
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     3,     4,    28,    17,    29,    18,    19,    30,    31,
      32,    50,    51,    52
  };

  const signed char
  parser::yytable_[] =
  {
      43,    53,    54,    55,    56,    11,    12,     7,     1,     5,
       1,    46,    47,    62,    46,    47,    46,    47,    72,    73,
      76,    77,    78,     2,    57,     2,    98,    73,     6,    84,
      85,    86,    87,    88,    89,    90,    91,    48,    93,     9,
      48,    49,    48,    81,    94,    95,    64,    65,    66,    67,
      68,    69,    10,    13,    64,    65,    66,    67,    68,    69,
      66,    67,    68,    69,    70,    71,    14,    16,    20,   102,
      34,    74,    70,    71,    38,    35,    70,    71,    40,    75,
      64,    65,    66,    67,    68,    69,    36,    37,    42,    41,
      58,    21,    44,    45,    59,    61,    60,    63,    70,    71,
      22,    96,    23,    92,    24,    83,    97,    79,    25,    26,
      80,   100,    27,    99,    14,    64,    65,    66,    67,    68,
      69,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
     101,   103,     8,    70,    71,    15,   104,    39,    70,    71,
      33,    82,    -1,    -1
  };

  const signed char
  parser::yycheck_[] =
  {
      30,    36,    37,    11,    12,    18,    19,     0,     1,    25,
       1,     3,     4,    48,     3,     4,     3,     4,    30,    31,
      55,    56,    57,    16,    32,    16,    30,    31,     4,    64,
      65,    66,    67,    68,    69,    70,    71,    29,    73,    25,
      29,    30,    29,    30,    74,    75,     5,     6,     7,     8,
       9,    10,    26,    25,     5,     6,     7,     8,     9,    10,
       7,     8,     9,    10,    23,    24,    27,    16,     4,    99,
      25,    30,    23,    24,     4,    29,    23,    24,    24,    30,
       5,     6,     7,     8,     9,    10,    29,    29,    28,    24,
       4,     4,    25,    20,     4,    29,    25,    25,    23,    24,
      13,     4,    15,    25,    17,    30,     4,    31,    21,    22,
      31,    23,    25,    14,    27,     5,     6,     7,     8,     9,
      10,     6,     7,     8,     9,    10,     7,     8,     9,    10,
      23,    25,     3,    23,    24,    12,    25,    24,    23,    24,
      18,    61,    23,    24
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,    16,    34,    35,    25,     4,     0,    35,    25,
      26,    18,    19,    25,    27,    36,    16,    37,    39,    40,
       4,     4,    13,    15,    17,    21,    22,    25,    36,    38,
      41,    42,    43,    40,    25,    29,    29,    29,     4,    45,
      24,    24,    28,    42,    25,    20,     3,     4,    29,    30,
      44,    45,    46,    44,    44,    11,    12,    32,     4,     4,
      25,    29,    44,    25,     5,     6,     7,     8,     9,    10,
      23,    24,    30,    31,    30,    30,    44,    44,    44,    31,
      31,    30,    46,    30,    44,    44,    44,    44,    44,    44,
      44,    44,    25,    44,    42,    42,     4,     4,    30,    14,
      23,    23,    42,    25,    25
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    33,    34,    34,    35,    35,    35,    36,    37,    37,
      38,    38,    39,    39,    40,    41,    41,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    43,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    45,    46,    46
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     5,     5,     4,     0,     1,
       0,     1,     1,     2,     5,     1,     2,     1,     2,     5,
       4,     5,     7,     5,     7,     7,     1,     4,     4,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     4,     3,     1,     1,     3
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
  "\"load\"", "\"store\"", "'>'", "'<'", "';'", "':'", "'{'", "'}'", "'('",
  "')'", "','", "'='", "$accept", "unit", "define_or_state", "block",
  "decl_list", "state_list", "decls", "declaration", "states", "statement",
  "assign", "expr", "value", "args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    94,    94,    95,    98,    99,   100,   103,   106,   107,
     110,   111,   114,   115,   118,   121,   122,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   137,   138,   139,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   157,   160,   161
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
      29,    30,     2,     2,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    25,
      24,    32,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
    };
    // Last valid token kind.
    const int code_max = 277;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1529 "parser.cc"

#line 164 "parser.y"

void yy::parser::error(const yy::parser::location_type& l, const std::string& m) {
    driver.error(l, m);
}
