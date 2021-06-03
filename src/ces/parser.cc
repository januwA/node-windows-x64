// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// Take the name prefix into account.
#define yylex   ceslex



#include "parser.h"


// Unqualified %code blocks.

	#include <iostream>
	#include "BaseNode.h"

	extern ces::parser::symbol_type yylex (std::string_view source);



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
#if CESDEBUG

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

#else // !CESDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !CESDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace ces {

  /// Build a parser object.
  parser::parser (BaseNode** result_yyarg, std::string_view source_yyarg)
#if CESDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      result (result_yyarg),
      source (source_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CEAddressString: // CEAddressString
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_atom: // atom
        value.YY_MOVE_OR_COPY< BaseNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX: // "hex"
      case symbol_kind::S_IDENT: // "ident"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identList: // identList
        value.YY_MOVE_OR_COPY< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CEAddressString: // CEAddressString
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_atom: // atom
        value.move< BaseNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX: // "hex"
      case symbol_kind::S_IDENT: // "ident"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identList: // identList
        value.move< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CEAddressString: // CEAddressString
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_atom: // atom
        value.copy< BaseNode* > (that.value);
        break;

      case symbol_kind::S_HEX: // "hex"
      case symbol_kind::S_IDENT: // "ident"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_identList: // identList
        value.copy< std::vector<std::string>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CEAddressString: // CEAddressString
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_atom: // atom
        value.move< BaseNode* > (that.value);
        break;

      case symbol_kind::S_HEX: // "hex"
      case symbol_kind::S_IDENT: // "ident"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_identList: // identList
        value.move< std::vector<std::string>* > (that.value);
        break;

      default:
        break;
    }

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
  }

#if CESDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
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
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if CESDEBUG
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
#endif // CESDEBUG

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
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
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
            symbol_type yylookahead (yylex (source));
            yyla.move (yylookahead);
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_CEAddressString: // CEAddressString
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_atom: // atom
        yylhs.value.emplace< BaseNode* > ();
        break;

      case symbol_kind::S_HEX: // "hex"
      case symbol_kind::S_IDENT: // "ident"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_identList: // identList
        yylhs.value.emplace< std::vector<std::string>* > ();
        break;

      default:
        break;
    }


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
  case 2: // CEAddressString: binaryExpr $end
                                  { *result = yystack_[1].value.as < BaseNode* > (); yylhs.value.as < BaseNode* > () = yystack_[1].value.as < BaseNode* > (); }
    break;

  case 3: // binaryExpr: atom
                 { yylhs.value.as < BaseNode* > () = yystack_[0].value.as < BaseNode* > (); }
    break;

  case 4: // binaryExpr: unaryExpr
            { yylhs.value.as < BaseNode* > () = yystack_[0].value.as < BaseNode* > (); }
    break;

  case 5: // binaryExpr: binaryExpr "+" binaryExpr
                             { yylhs.value.as < BaseNode* > () = new BinaryNode(yystack_[2].value.as < BaseNode* > (), token::PLUS, yystack_[0].value.as < BaseNode* > (), yystack_[2].location += yystack_[0].location); }
    break;

  case 6: // binaryExpr: binaryExpr "-" binaryExpr
                              { yylhs.value.as < BaseNode* > () = new BinaryNode(yystack_[2].value.as < BaseNode* > (), token::MINUS, yystack_[0].value.as < BaseNode* > (),yystack_[2].location += yystack_[0].location); }
    break;

  case 7: // binaryExpr: binaryExpr "*" binaryExpr
                            { yylhs.value.as < BaseNode* > () = new BinaryNode(yystack_[2].value.as < BaseNode* > (), token::MUL, yystack_[0].value.as < BaseNode* > (), yystack_[2].location += yystack_[0].location); }
    break;

  case 8: // binaryExpr: binaryExpr "/" binaryExpr
                            { yylhs.value.as < BaseNode* > () = new BinaryNode(yystack_[2].value.as < BaseNode* > (), token::DIV, yystack_[0].value.as < BaseNode* > (), yystack_[2].location += yystack_[0].location); }
    break;

  case 9: // binaryExpr: binaryExpr "**" binaryExpr
                            { yylhs.value.as < BaseNode* > () = new BinaryNode(yystack_[2].value.as < BaseNode* > (), token::POW, yystack_[0].value.as < BaseNode* > (), yystack_[2].location += yystack_[0].location); }
    break;

  case 10: // unaryExpr: "+" atom
                     { yylhs.value.as < BaseNode* > () = new UnaryNode(token::PLUS, yystack_[0].value.as < BaseNode* > (), yystack_[1].location+yystack_[0].location); }
    break;

  case 11: // unaryExpr: "-" atom
             { yylhs.value.as < BaseNode* > () = new UnaryNode(token::MINUS, yystack_[0].value.as < BaseNode* > (), yystack_[1].location+yystack_[0].location); }
    break;

  case 12: // atom: "hex"
                { yylhs.value.as < BaseNode* > () = new HexNode(yystack_[0].value.as < std::string > (), yystack_[0].location); }
    break;

  case 13: // atom: "[" binaryExpr "]"
                     { yylhs.value.as < BaseNode* > () = new PointerNode(yystack_[1].value.as < BaseNode* > (), yystack_[2].location+yystack_[0].location); }
    break;

  case 14: // atom: identList
                { yylhs.value.as < BaseNode* > () = new IdentsNode(yystack_[0].value.as < std::vector<std::string>* > (), yystack_[0].location);}
    break;

  case 15: // identList: "ident"
                 { yylhs.value.as < std::vector<std::string>* > () = new std::vector<std::string>{yystack_[0].value.as < std::string > ()}; }
    break;

  case 16: // identList: identList "." "ident"
                        { yylhs.value.as < std::vector<std::string>* > () = yystack_[2].value.as < std::vector<std::string>* > (); yylhs.value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ()); }
    break;



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
        std::string msg = YY_("syntax error");
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

#if CESDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if CESDEBUG || 0





  const signed char parser::yypact_ninf_ = -6;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      13,    -6,    -6,    17,    17,    13,     2,     1,    -6,    -6,
      10,    -6,    -6,    23,    -6,    -6,    13,    13,    13,    13,
      13,    22,    -6,    -4,    -4,    24,    24,    -6,    -6
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    12,    15,     0,     0,     0,     0,     0,     4,     3,
      14,    10,    11,     0,     1,     2,     0,     0,     0,     0,
       0,     0,    13,     5,     6,     7,     8,     9,    16
  };

  const signed char
  parser::yypgoto_[] =
  {
      -6,    -6,    -5,    -6,    21,    -6
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     6,     7,     8,     9,    10
  };

  const signed char
  parser::yytable_[] =
  {
      13,    15,    14,    18,    19,    20,    16,    17,    18,    19,
      20,    23,    24,    25,    26,    27,     1,     2,     3,     4,
       1,     2,    21,     5,    11,    12,    28,     5,    16,    17,
      18,    19,    20,    20,    22
  };

  const signed char
  parser::yycheck_[] =
  {
       5,     0,     0,     7,     8,     9,     5,     6,     7,     8,
       9,    16,    17,    18,    19,    20,     3,     4,     5,     6,
       3,     4,    12,    10,     3,     4,     4,    10,     5,     6,
       7,     8,     9,     9,    11
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,    10,    14,    15,    16,    17,
      18,    17,    17,    15,     0,     0,     5,     6,     7,     8,
       9,    12,    11,    15,    15,    15,    15,    15,     4
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    13,    14,    15,    15,    15,    15,    15,    15,    15,
      16,    16,    17,    17,    17,    18,    18
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     3,     3,     3,     3,     3,
       2,     2,     1,     3,     1,     1,     3
  };


#if CESDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"hex\"", "\"ident\"",
  "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"**\"", "\"[\"", "\"]\"", "\".\"",
  "$accept", "CEAddressString", "binaryExpr", "unaryExpr", "atom",
  "identList", YY_NULLPTR
  };
#endif


#if CESDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    39,    39,    42,    43,    44,    45,    46,    47,    48,
      51,    52,    55,    56,    57,    60,    61
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
#endif // CESDEBUG


} // ces



void ces::parser::error(const location_type& loc, const std::string& msg)
{
  throw ces::parser_error(source, loc);
}
