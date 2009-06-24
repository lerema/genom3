
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   G3nomlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 30 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
 /*** C/C++ Declarations ***/

#include <cstdio>
#include <string>
#include <vector>
// #include <boost/variant.hpp>

#include "utils/ast.h"
#include "utils/idltype.h"

using namespace G3nom;
using namespace Idl;

/* Line 311 of lalr1.cc  */
#line 216 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"


#include "driver.h"
#include "lexer.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer()->lex



/* Line 311 of lalr1.cc  */
#line 72 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"


#include "parser.hpp"

/* User implementation prologue.  */


/* Line 317 of lalr1.cc  */
#line 81 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace G3nom {

/* Line 380 of lalr1.cc  */
#line 150 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              /* Fall through.  */
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

#endif

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 95 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = driver.streamNamePtr();
}

/* Line 553 of lalr1.cc  */
#line 334 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 4:

/* Line 678 of lalr1.cc  */
#line 237 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 242 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 244 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 246 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 248 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 250 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.component().addType((yysemantic_stack_[(1) - (1)].typeVal));
}
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 254 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 261 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.component().setName((yysemantic_stack_[(5) - (2)].stringVal));
}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 268 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 273 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    if((yysemantic_stack_[(3) - (1)].stringVal) == "language") {
	driver.component().pluginLanguage = (yysemantic_stack_[(3) - (3)].stringVal);
    } else if((yysemantic_stack_[(3) - (1)].stringVal) == "version") {
	driver.component().version = (yysemantic_stack_[(3) - (3)].stringVal);
    } else {
      error(yyloc, std::string("Unknown component field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }
}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 284 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    if((yysemantic_stack_[(3) - (1)].stringVal) == "uniqueId") {
	driver.component().uniqueId = (yysemantic_stack_[(3) - (3)].integerVal);
    } else {
      error(yyloc, std::string("Unknown component field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 292 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    if((yysemantic_stack_[(3) - (1)].stringVal) == "ids") {
	Idl::IdlType::Ptr p = driver.component().typeFromName((yysemantic_stack_[(3) - (3)].stringVal));
	if(!p.get()) {
	    error(yyloc, std::string("Unknown type: ") + (yysemantic_stack_[(3) - (3)].stringVal));
	    YYERROR;
	}
	driver.component().IDSType = p;
    } else if((yysemantic_stack_[(3) - (1)].stringVal) == "requires") {
	driver.component().addImportedComponent((yysemantic_stack_[(3) - (3)].stringVal));
    } else {
      error(yyloc, std::string("Unknown component field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }
}
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 312 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Idl::IdlType::Ptr type = driver.component().typeFromName((yysemantic_stack_[(3) - (2)].stringVal));
    if(!type.get()) {
	error(yyloc, std::string("Unknown type: ") + (yysemantic_stack_[(3) - (2)].stringVal));
	YYERROR;
    }
    Port::Ptr p(new Port((yysemantic_stack_[(3) - (3)].stringVal), type, true));
    driver.component().addPort(p);
}
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 322 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Idl::IdlType::Ptr type = driver.component().typeFromName((yysemantic_stack_[(3) - (2)].stringVal));
    if(!type.get()) {
	error(yyloc, std::string("Unknown type: ") + (yysemantic_stack_[(3) - (2)].stringVal));
	YYERROR;
    }
    Port::Ptr p(new Port((yysemantic_stack_[(3) - (3)].stringVal), type, false));
    driver.component().addPort(p);
}
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 332 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Idl::IdlType::Ptr type = driver.component().typeFromName((yysemantic_stack_[(10) - (2)].stringVal));
    if(!type.get()) {
	error(yyloc, std::string("Unknown type: ") + (yysemantic_stack_[(10) - (2)].stringVal));
	YYERROR;
    }
    Port::Ptr p(new Port((yysemantic_stack_[(10) - (3)].stringVal), type, false));
    if((yysemantic_stack_[(10) - (6)].stringVal) == "size")
      p->sizeCodel = (yysemantic_stack_[(10) - (8)].codelVal);
    else {
	error(yyloc, std::string("Unknown codel for an outport : ") + (yysemantic_stack_[(10) - (6)].stringVal));
	YYERROR;
    }
    driver.component().addPort(p);
}
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 352 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Task::Ptr t(new Task((yysemantic_stack_[(2) - (2)].stringVal)));
    driver.setCurrentTask(t);
}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 357 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.component().addTask(driver.currentTask());
}
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 364 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 368 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentTask()->addCodel((yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].codelVal));
}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 372 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Task::Ptr t = driver.currentTask();

    if((yysemantic_stack_[(3) - (1)].stringVal) == "priority")
      t->priority = (yysemantic_stack_[(3) - (3)].integerVal);
    else if((yysemantic_stack_[(3) - (1)].stringVal) == "period")
      t->period = (yysemantic_stack_[(3) - (3)].integerVal);
    else if((yysemantic_stack_[(3) - (1)].stringVal) == "delay")
      t->delay = (yysemantic_stack_[(3) - (3)].integerVal);
    else if((yysemantic_stack_[(3) - (1)].stringVal) == "stackSize")
      t->stackSize = (yysemantic_stack_[(3) - (3)].integerVal);
    else {
      error(yyloc, std::string("Unknown task field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }
}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 389 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    if((yysemantic_stack_[(3) - (1)].stringVal) != "errors") {
      error(yyloc, std::string("Wrong arguments for field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }
}
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 398 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentTask()->addErrorMessage((yysemantic_stack_[(1) - (1)].stringVal));
}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 402 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentTask()->addErrorMessage((yysemantic_stack_[(2) - (2)].stringVal));
}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 410 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Service::Ptr s(new Service((yysemantic_stack_[(2) - (2)].stringVal)));
    driver.setCurrentService(s);
}
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 415 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.component().addService(driver.currentService());
}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 422 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 426 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentService()->addCodel((yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].codelVal));
}
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 430 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
}
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 433 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentService()->output = (yysemantic_stack_[(3) - (3)].serviceInputVal);
}
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 437 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Service::Ptr s = driver.currentService();

    if((yysemantic_stack_[(4) - (4)].stringVal) == "") {
	if((yysemantic_stack_[(4) - (1)].stringVal) == "type") {
	    if((yysemantic_stack_[(4) - (3)].stringVal) == "init")
	      s->type = Service::Init;
	    else if((yysemantic_stack_[(4) - (3)].stringVal) == "control")
	      s->type = Service::Control;
	    else if((yysemantic_stack_[(4) - (3)].stringVal) == "exec")
	      s->type = Service::Exec;
	    else {
	      error(yyloc, std::string("Unknown service type: ") + (yysemantic_stack_[(4) - (3)].stringVal));
	      YYERROR;
	    }
	} else if((yysemantic_stack_[(4) - (1)].stringVal) == "taskName") {
	    s->taskName = (yysemantic_stack_[(4) - (3)].stringVal);
	} else if((yysemantic_stack_[(4) - (1)].stringVal) == "errors") {
	    driver.currentService()->addErrorMessage((yysemantic_stack_[(4) - (3)].stringVal));
	} else if((yysemantic_stack_[(4) - (1)].stringVal) == "interrupts") {
	    driver.currentService()->addIncompatibleService((yysemantic_stack_[(4) - (3)].stringVal));
	} else {
	  error(yyloc, std::string("Unknown service field: ") + (yysemantic_stack_[(4) - (1)].stringVal));
	  YYERROR;
	}
    } else {
	std::vector<std::string> ids;
	driver.split((yysemantic_stack_[(4) - (4)].stringVal), ids);
	std::vector<std::string>::const_iterator it = ids.begin();

	if((yysemantic_stack_[(4) - (1)].stringVal) == "errors") {
	    driver.currentService()->addErrorMessage((yysemantic_stack_[(4) - (3)].stringVal));
	    for(; it != ids.end(); ++it)
		driver.currentService()->addErrorMessage(*it);
	} else if ((yysemantic_stack_[(4) - (1)].stringVal) == "interrupts") {
	    driver.currentService()->addIncompatibleService((yysemantic_stack_[(4) - (3)].stringVal));
	    for(; it != ids.end(); ++it)
		driver.currentService()->addIncompatibleService(*it);
	} else {
	  error(yyloc, std::string("Unknown service field (or wrong number of arguments): ") + (yysemantic_stack_[(4) - (1)].stringVal));
	  YYERROR;
	}
    }
}
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 482 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Service::Ptr s = driver.currentService();
    if((yysemantic_stack_[(3) - (1)].stringVal) == "doc") {
      s->doc = (yysemantic_stack_[(3) - (3)].stringVal);
    } else {
      error(yyloc, std::string("Unknown service field: ") + (yysemantic_stack_[(3) - (1)].stringVal));
      YYERROR;
    }
}
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 492 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 496 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.stringVal) = "";
}
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 500 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.stringVal) = (yysemantic_stack_[(1) - (1)].stringVal);
}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 506 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
   (yyval.stringVal) = (yysemantic_stack_[(1) - (1)].stringVal);
}
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 510 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.stringVal) = (yysemantic_stack_[(2) - (1)].stringVal) + " " + (yysemantic_stack_[(2) - (2)].stringVal);
}
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 516 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 518 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 522 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yysemantic_stack_[(3) - (1)].serviceInputVal).defaultValue = (yysemantic_stack_[(3) - (3)].literalVal);
    driver.currentService()->addInput((yysemantic_stack_[(3) - (1)].serviceInputVal));
}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 527 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentService()->addInput((yysemantic_stack_[(1) - (1)].serviceInputVal));
}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 533 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    // check if the name given is in the ids
    Idl::IdlType::Ptr t = driver.component().typeFromIdsName((yysemantic_stack_[(3) - (3)].stringVal));
    if(!t.get()) {
      error(yyloc, std::string("Input is not in the IDS: ") + (yysemantic_stack_[(3) - (3)].stringVal));
      YYERROR;
    }

    Service::Input i;
    i.kind = Service::Input::IDSMember;
    i.identifier = (yysemantic_stack_[(3) - (3)].stringVal);
    (yyval.serviceInputVal) = i;
}
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 547 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Service::Input i;
    i.kind = Service::Input::Type;
    i.identifier = (yysemantic_stack_[(2) - (2)].stringVal);
    i.type = (yysemantic_stack_[(2) - (1)].typeVal);
    (yyval.serviceInputVal) = i;
}
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 559 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Codel::Ptr c(new Codel((yysemantic_stack_[(1) - (1)].stringVal)));
    driver.setCurrentCodel(c);
}
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 564 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.codelVal) = driver.currentCodel();
}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 570 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 572 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 574 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 578 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    // check if the name given is in the ids
    Idl::IdlType::Ptr t = driver.component().typeFromIdsName((yysemantic_stack_[(2) - (2)].stringVal));
    if(!t.get()) {
      error(yyloc, std::string("Input is not in the IDS: ") + (yysemantic_stack_[(2) - (2)].stringVal));
      YYERROR;
    }

    driver.currentCodel()->addInType((yysemantic_stack_[(2) - (2)].stringVal));
}
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 589 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    // check if the name given is in the ids
    Idl::IdlType::Ptr t = driver.component().typeFromIdsName((yysemantic_stack_[(2) - (2)].stringVal));
    if(!t.get()) {
      error(yyloc, std::string("Output is not in the IDS: ") + (yysemantic_stack_[(2) - (2)].stringVal));
      YYERROR;
    }

    driver.currentCodel()->addOutType((yysemantic_stack_[(2) - (2)].stringVal));
}
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 600 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentCodel()->addInPort((yysemantic_stack_[(2) - (2)].stringVal));
}
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 604 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    driver.currentCodel()->addOutPort((yysemantic_stack_[(2) - (2)].stringVal));
}
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 612 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    ConstValue c((yysemantic_stack_[(5) - (3)].stringVal), (yysemantic_stack_[(5) - (2)].typeVal), (yysemantic_stack_[(5) - (5)].literalVal));
    driver.component().addConstValue(c);
}
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 632 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal((yysemantic_stack_[(1) - (1)].integerVal));
}
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 636 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal((yysemantic_stack_[(1) - (1)].doubleVal));
}
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 640 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal("\"" + (yysemantic_stack_[(1) - (1)].stringVal) + "\"");
}
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 644 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal((yysemantic_stack_[(1) - (1)].charVal));
}
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 648 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = (yysemantic_stack_[(1) - (1)].literalVal);
}
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 652 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    /*enum value*/
    (yyval.literalVal) = Literal((yysemantic_stack_[(1) - (1)].stringVal));
}
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 657 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = (yysemantic_stack_[(3) - (2)].literalVal);
}
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 661 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = (yysemantic_stack_[(3) - (2)].literalVal);
}
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 665 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 669 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal(true);
}
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 673 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = Literal(false);
}
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 680 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Neg);
    l.addMember((yysemantic_stack_[(2) - (2)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 686 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.literalVal) = (yysemantic_stack_[(2) - (2)].literalVal);
}
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 690 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::LNeg);
    l.addMember((yysemantic_stack_[(2) - (2)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 697 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Plus);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 704 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Minus);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 711 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Times);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 718 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Divide);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 725 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Mod);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 732 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::And);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 739 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Or);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 89:

/* Line 678 of lalr1.cc  */
#line 746 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Xor);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 753 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::LShift);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 760 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::RShift);
    l.addMember((yysemantic_stack_[(3) - (1)].literalVal));
    l.addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 769 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Literal l(Literal::Struct);
    l.addMember((yysemantic_stack_[(1) - (1)].literalVal));
    (yyval.literalVal) = l;
}
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 775 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yysemantic_stack_[(3) - (1)].literalVal).addMember((yysemantic_stack_[(3) - (3)].literalVal));
    (yyval.literalVal) = (yysemantic_stack_[(3) - (1)].literalVal);
}
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 784 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p(new TypedefType((yysemantic_stack_[(3) - (2)].typeVal), (yysemantic_stack_[(3) - (3)].declaratorVectVal)));
    (yyval.typeVal) = p;
}
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 788 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 790 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 792 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yysemantic_stack_[(2) - (2)].typeVal)->setNative(true);
    (yyval.typeVal) = (yysemantic_stack_[(2) - (2)].typeVal);
}
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 807 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal);
}
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 811 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { 
    (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal);
}
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 816 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 817 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 102:

/* Line 678 of lalr1.cc  */
#line 819 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr type = driver.component().typeFromName((yysemantic_stack_[(1) - (1)].stringVal));
    if(!type.get()) {
	error(yyloc, std::string("Unknown type: ") + (yysemantic_stack_[(1) - (1)].stringVal));
	YYERROR;
    }
    (yyval.typeVal) = type;
}
    break;

  case 103:

/* Line 678 of lalr1.cc  */
#line 829 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 830 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 105:

/* Line 678 of lalr1.cc  */
#line 831 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 832 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 833 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 834 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 835 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 110:

/* Line 678 of lalr1.cc  */
#line 841 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 111:

/* Line 678 of lalr1.cc  */
#line 842 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 843 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 844 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 114:

/* Line 678 of lalr1.cc  */
#line 848 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 850 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 116:

/* Line 678 of lalr1.cc  */
#line 855 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { 
    Declarator::VectPtr v(new Declarator::Vect());
    v->push_back((yysemantic_stack_[(1) - (1)].declaratorVal));
    (yyval.declaratorVectVal) = v;
}
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 861 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
      if((yysemantic_stack_[(3) - (1)].declaratorVectVal)) {
	  (yysemantic_stack_[(3) - (1)].declaratorVectVal)->push_back((yysemantic_stack_[(3) - (3)].declaratorVal));
	  (yyval.declaratorVectVal) = (yysemantic_stack_[(3) - (1)].declaratorVectVal); 
      } else {
	  error(yyloc, "Problem with declarator map");
	  YYERROR;
      }  
}
    break;

  case 118:

/* Line 678 of lalr1.cc  */
#line 872 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.declaratorVal) = (yysemantic_stack_[(1) - (1)].declaratorVal); }
    break;

  case 119:

/* Line 678 of lalr1.cc  */
#line 873 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.declaratorVal) = (yysemantic_stack_[(1) - (1)].declaratorVal); }
    break;

  case 120:

/* Line 678 of lalr1.cc  */
#line 878 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    Declarator::Ptr p(new Declarator((yysemantic_stack_[(1) - (1)].stringVal)));
    (yyval.declaratorVal) = p;
}
    break;

  case 121:

/* Line 678 of lalr1.cc  */
#line 885 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yysemantic_stack_[(2) - (1)].declaratorVal)->addBound((yysemantic_stack_[(2) - (2)].integerVal));
    (yyval.declaratorVal) = (yysemantic_stack_[(2) - (1)].declaratorVal);
}
    break;

  case 122:

/* Line 678 of lalr1.cc  */
#line 890 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yysemantic_stack_[(2) - (1)].declaratorVal)->addBound((yysemantic_stack_[(2) - (2)].integerVal));
    (yyval.declaratorVal) = (yysemantic_stack_[(2) - (1)].declaratorVal);
}
    break;

  case 123:

/* Line 678 of lalr1.cc  */
#line 897 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.integerVal) = (yysemantic_stack_[(3) - (2)].integerVal);
}
    break;

  case 124:

/* Line 678 of lalr1.cc  */
#line 905 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::floatType; }
    break;

  case 125:

/* Line 678 of lalr1.cc  */
#line 906 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::doubleType; }
    break;

  case 126:

/* Line 678 of lalr1.cc  */
#line 907 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::longdoubleType; }
    break;

  case 127:

/* Line 678 of lalr1.cc  */
#line 912 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p(new FixedType((yysemantic_stack_[(6) - (3)].integerVal), (yysemantic_stack_[(6) - (5)].integerVal)));
    (yyval.typeVal) = p;
}
    break;

  case 128:

/* Line 678 of lalr1.cc  */
#line 917 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 129:

/* Line 678 of lalr1.cc  */
#line 920 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 130:

/* Line 678 of lalr1.cc  */
#line 921 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 131:

/* Line 678 of lalr1.cc  */
#line 925 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 132:

/* Line 678 of lalr1.cc  */
#line 926 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 133:

/* Line 678 of lalr1.cc  */
#line 927 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 134:

/* Line 678 of lalr1.cc  */
#line 931 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::shortType; }
    break;

  case 135:

/* Line 678 of lalr1.cc  */
#line 935 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::longType; }
    break;

  case 136:

/* Line 678 of lalr1.cc  */
#line 939 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::longlongType; }
    break;

  case 137:

/* Line 678 of lalr1.cc  */
#line 943 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 138:

/* Line 678 of lalr1.cc  */
#line 944 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 139:

/* Line 678 of lalr1.cc  */
#line 945 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = (yysemantic_stack_[(1) - (1)].typeVal); }
    break;

  case 140:

/* Line 678 of lalr1.cc  */
#line 949 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::ushortType; }
    break;

  case 141:

/* Line 678 of lalr1.cc  */
#line 953 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::ulongType; }
    break;

  case 142:

/* Line 678 of lalr1.cc  */
#line 957 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::ulonglongType; }
    break;

  case 143:

/* Line 678 of lalr1.cc  */
#line 961 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::charType; }
    break;

  case 144:

/* Line 678 of lalr1.cc  */
#line 965 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::wcharType; }
    break;

  case 145:

/* Line 678 of lalr1.cc  */
#line 969 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::booleanType; }
    break;

  case 146:

/* Line 678 of lalr1.cc  */
#line 973 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::octetType; }
    break;

  case 147:

/* Line 678 of lalr1.cc  */
#line 977 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { (yyval.typeVal) = BaseType::anyType; }
    break;

  case 148:

/* Line 678 of lalr1.cc  */
#line 986 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p(new StringType((yysemantic_stack_[(4) - (3)].integerVal)));
    (yyval.typeVal) = p; 
}
    break;

  case 149:

/* Line 678 of lalr1.cc  */
#line 991 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.typeVal) = StringType::unboundedStringType;
}
    break;

  case 150:

/* Line 678 of lalr1.cc  */
#line 997 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    { 
    IdlType::Ptr p(new WStringType((yysemantic_stack_[(4) - (3)].integerVal)));
    (yyval.typeVal) = p; 
}
    break;

  case 151:

/* Line 678 of lalr1.cc  */
#line 1002 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    (yyval.typeVal) = WStringType::unboundedWStringType;
}
    break;

  case 152:

/* Line 678 of lalr1.cc  */
#line 1012 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p = driver.currentType();
    StructType *s = static_cast<StructType*>(p.get());
    if(!s) {
	error(yyloc, "Empty struct ??");
	YYERROR;
    }
    s->setIdentifier((yysemantic_stack_[(5) - (2)].stringVal));
    driver.setCurrentType(IdlType::Ptr());
    (yyval.typeVal) = p;
}
    break;

  case 153:

/* Line 678 of lalr1.cc  */
#line 1026 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 154:

/* Line 678 of lalr1.cc  */
#line 1028 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 155:

/* Line 678 of lalr1.cc  */
#line 1032 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    StructType *s = dynamic_cast<StructType*>(driver.currentType().get());
    if(!s) {
	IdlType::Ptr p(new StructType());
	s = dynamic_cast<StructType*>(p.get());
	driver.setCurrentType(p);
    }
    s->addMember((yysemantic_stack_[(3) - (1)].typeVal), (yysemantic_stack_[(3) - (2)].declaratorVectVal));
}
    break;

  case 156:

/* Line 678 of lalr1.cc  */
#line 1118 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p = driver.currentType();
    EnumType *s = dynamic_cast<EnumType*>(p.get());
    if(!s) {
	error(yyloc, "Empty enum ??");
	YYERROR;
    }
    s->setIdentifier((yysemantic_stack_[(5) - (2)].stringVal));
    driver.setCurrentType(IdlType::Ptr());
    (yyval.typeVal) = p;
}
    break;

  case 157:

/* Line 678 of lalr1.cc  */
#line 1131 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 158:

/* Line 678 of lalr1.cc  */
#line 1133 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {}
    break;

  case 159:

/* Line 678 of lalr1.cc  */
#line 1137 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    EnumType *s = dynamic_cast<EnumType*>(driver.currentType().get());
    if(!s) {
	IdlType::Ptr e(new EnumType());
	s =  dynamic_cast<EnumType*>(e.get());
	driver.setCurrentType(e);
    }
    s->addEnumerator((yysemantic_stack_[(1) - (1)].stringVal));
}
    break;

  case 160:

/* Line 678 of lalr1.cc  */
#line 1151 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p(new SequenceType((yysemantic_stack_[(6) - (3)].typeVal), (yysemantic_stack_[(6) - (5)].integerVal)));
    (yyval.typeVal) = p;
}
    break;

  case 161:

/* Line 678 of lalr1.cc  */
#line 1156 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
    {
    IdlType::Ptr p(new SequenceType((yysemantic_stack_[(4) - (3)].typeVal), 0));  
    (yyval.typeVal) = p;
}
    break;



/* Line 678 of lalr1.cc  */
#line 1874 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -212;
  const short int
  Parser::yypact_[] =
  {
       129,   -39,   -29,   -26,   -16,    16,    -2,    20,    69,   251,
     185,    79,   101,   120,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,   123,  -212,  -212,    81,    84,  -212,   128,   137,
    -212,    50,  -212,  -212,   136,  -212,  -212,   149,   150,  -212,
    -212,   -18,   107,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,   153,  -212,   108,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,   158,  -212,   113,   162,   163,  -212,   165,
     132,   185,  -212,  -212,   138,   139,   140,  -212,   164,   177,
     218,  -212,   183,  -212,   130,   130,  -212,   187,    14,   211,
      11,    18,   215,  -212,    24,  -212,   108,    85,  -212,   210,
     212,   213,  -212,     6,    32,   108,   178,  -212,  -212,    40,
    -212,   217,  -212,   204,   219,     1,   253,   205,   255,   256,
     257,    15,   254,   214,  -212,   132,    -5,  -212,  -212,   216,
    -212,  -212,     6,     6,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,     6,     6,     6,    94,  -212,  -212,  -212,   220,  -212,
     200,  -212,  -212,  -212,  -212,   261,   -37,  -212,   276,  -212,
     277,   152,   152,    71,  -212,   279,  -212,   280,  -212,  -212,
     274,    94,    25,    26,  -212,  -212,  -212,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,   281,  -212,   234,
    -212,  -212,   236,  -212,   234,   282,   283,  -212,   278,   240,
    -212,  -212,  -212,   243,  -212,   234,  -212,  -212,     6,  -212,
     174,   174,   141,   141,   193,    38,    38,    38,    77,    77,
    -212,  -212,  -212,  -212,  -212,   244,   152,     6,  -212,  -212,
    -212,   245,   292,    94,   288,  -212,  -212,    94,  -212,   295,
      80,  -212,   249,   250,   252,   258,    65,  -212,  -212,  -212,
    -212,  -212,    80,  -212,  -212
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     5,     7,     8,    10,     9,
      95,    96,     0,    20,    29,     0,     0,    97,     0,     0,
     134,   135,   124,   125,   128,   143,   144,   149,   151,   145,
     146,     0,     0,    63,    66,    59,   129,   131,   132,   133,
     130,   137,   138,   139,    60,    61,    62,    67,    64,    65,
     147,     0,   102,     0,    98,   100,   101,    99,   103,   113,
     104,   105,   106,   107,   108,   109,   111,   112,   114,   115,
     110,     1,     2,     0,     3,     0,     0,     0,    17,    18,
       0,     0,   136,   126,     0,     0,     0,   140,   141,     0,
       0,   120,    94,   116,   118,   119,     4,     0,     0,     0,
       0,     0,     0,   159,     0,   157,     0,     0,   153,     0,
       0,     0,   142,     0,     0,     0,     0,   121,   122,     0,
      11,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,     0,     0,   152,   154,     0,
     148,   150,     0,     0,    77,    78,    71,    68,    69,    70,
      73,     0,     0,     0,    58,    72,    76,   161,     0,   117,
       0,    15,    14,    16,    13,     0,     0,    21,     0,    22,
       0,     0,     0,     0,    30,     0,    31,     0,   158,   155,
       0,    92,     0,     0,    79,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,     0,
      25,    27,    26,    23,     0,     0,    34,    43,    46,     0,
      35,    38,    37,    39,    32,     0,   127,    74,     0,    75,
      83,    82,    85,    84,    86,    89,    88,    87,    91,    90,
     160,    49,    24,    28,    33,     0,     0,     0,    48,    41,
      36,    40,     0,    93,     0,    47,    44,    45,    42,     0,
      51,    19,     0,     0,     0,     0,     0,    52,    54,    55,
      56,    57,     0,    50,    53
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -212,  -212,  -212,   294,  -212,  -212,   201,  -212,  -212,  -212,
    -212,   173,  -212,  -212,  -212,  -212,   169,  -212,  -212,  -212,
      66,   133,  -211,  -212,  -212,    39,  -212,  -212,  -151,  -212,
    -212,  -212,   308,   -10,   221,  -212,  -212,  -212,   202,   191,
    -212,  -212,   222,   310,   311,   313,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,   314,   315,   316,   317,  -212,   319,
     320,    19,  -212,   223,    30,  -212,   172,  -212
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,    11,    12,    13,    14,   108,   109,    15,    16,    86,
     135,   136,   212,    17,    87,   141,   142,   250,   251,   216,
     217,   218,   242,   254,   266,   267,    18,    42,   164,   165,
     166,   192,    19,   219,    64,    65,    66,    67,   102,   103,
     104,   105,   127,    68,    69,    70,    46,    47,    48,    49,
      50,    51,    52,    53,    71,    72,    73,    74,    75,    76,
      77,    78,   117,   118,    79,   114,   115,    80
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const short int
  Parser::yytable_[] =
  {
        63,   191,   193,   244,   189,    97,    98,   133,   125,   177,
     194,   195,   196,   152,   252,   210,    22,   133,   211,    20,
     153,   137,   130,   184,   137,    20,    23,   154,   155,    24,
      21,    20,   144,   227,     6,     7,    21,   145,   228,    25,
       8,   229,    21,    10,   167,   168,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   134,   156,   157,   158,
     159,   160,   161,   162,   138,   139,   134,   138,   139,   107,
     140,    26,   163,   140,    92,    28,    93,   253,   272,    81,
     273,   116,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   171,   147,   172,   173,   257,   262,   263,   264,
     265,    82,   205,   206,     1,     2,     3,   116,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    60,
       4,     5,     7,   221,    29,   222,   223,     8,    61,    84,
      85,    41,     1,     2,     3,    90,    88,     6,     7,    89,
      62,    -1,    -1,     8,    91,     9,    10,    94,     4,     5,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
      95,    96,    99,   101,   100,     6,     7,   106,   107,   110,
     111,     8,   112,     9,    10,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    60,   113,   122,     7,
     119,   120,   121,   123,     8,    61,   125,   129,    41,   126,
     215,   201,   202,   203,   204,   205,   206,    62,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    60,
     132,   143,     7,   149,   150,   151,   174,     8,    61,   176,
     170,    41,   199,   200,   201,   202,   203,   204,   205,   206,
      62,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    60,    -1,   202,   203,   204,   205,   206,   175,
     180,    61,   179,   186,    41,   181,   182,   183,   190,   187,
     208,   209,   207,    62,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   213,   226,   214,   224,   241,
     225,   243,   245,   240,   247,   248,   246,    41,   249,   255,
     258,   259,   260,   261,   268,   269,    83,   270,   178,   131,
     185,   274,   256,   271,    27,   220,   169,   188,   146,    43,
      44,   124,    45,    54,    55,    56,    57,   128,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        10,   152,   153,   214,     9,    23,    24,     6,    13,     8,
     161,   162,   163,     7,   225,    52,    55,     6,    55,     0,
      14,     6,     8,     8,     6,     6,    55,    21,    22,    55,
       0,    12,     8,     8,    36,    37,     6,    13,    13,    55,
      42,    15,    12,    45,    12,    13,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,    55,    51,    52,    53,
      54,    55,    56,    57,    49,    50,    55,    49,    50,    55,
      55,    55,    66,    55,    24,    55,    26,   228,    13,     0,
      15,    91,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    52,     8,    54,    55,   247,    17,    18,    19,
      20,     0,    64,    65,     3,     4,     5,   117,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      19,    20,    37,    52,    55,    54,    55,    42,    43,     9,
       7,    46,     3,     4,     5,     7,    55,    36,    37,    55,
      55,    64,    65,    42,     7,    44,    45,    11,    19,    20,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      11,    11,    55,    55,    11,    36,    37,     9,    55,     7,
       7,    42,     7,    44,    45,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    55,    24,    37,
      52,    52,    52,    16,    42,    43,    13,    10,    46,    69,
      48,    60,    61,    62,    63,    64,    65,    55,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       9,     6,    37,    13,    12,    12,     9,    42,    43,    10,
      52,    46,    58,    59,    60,    61,    62,    63,    64,    65,
      55,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    60,    61,    62,    63,    64,    65,    55,
      55,    43,     9,     9,    46,    10,    10,    10,    52,    55,
      70,    10,    52,    55,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     9,    12,    10,     9,    55,
      10,    55,    10,    12,    16,    55,    13,    46,    55,    55,
      55,     9,    14,     8,    55,    55,    12,    55,   135,   108,
     141,   272,   246,    55,     6,   182,   125,   145,   116,     9,
       9,   100,     9,     9,     9,     9,     9,   105,     9,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     3,     4,     5,    19,    20,    36,    37,    42,    44,
      45,    72,    73,    74,    75,    78,    79,    84,    97,   103,
     132,   135,    55,    55,    55,    55,    55,   103,    55,    55,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    46,    98,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   130,   131,
      34,    43,    55,   104,   105,   106,   107,   108,   114,   115,
     116,   125,   126,   127,   128,   129,   130,   131,   132,   135,
     138,     0,     0,    74,     9,     7,    80,    85,    55,    55,
       7,     7,    24,    26,    11,    11,    11,    23,    24,    55,
      11,    55,   109,   110,   111,   112,     9,    55,    76,    77,
       7,     7,     7,    55,   136,   137,   104,   133,   134,    52,
      52,    52,    24,    16,   105,    13,    69,   113,   113,    10,
       8,    77,     9,     6,    55,    81,    82,     6,    49,    50,
      55,    86,    87,     6,     8,    13,   109,     8,   134,    13,
      12,    12,     7,    14,    21,    22,    51,    52,    53,    54,
      55,    56,    57,    66,    99,   100,   101,    12,    13,   110,
      52,    52,    54,    55,     9,    55,    10,     8,    82,     9,
      55,    10,    10,    10,     8,    87,     9,    55,   137,     9,
      52,    99,   102,    99,    99,    99,    99,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    52,    70,    10,
      52,    55,    83,     9,    10,    48,    90,    91,    92,   104,
      92,    52,    54,    55,     9,    10,    12,     8,    13,    15,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      12,    55,    93,    55,    93,    10,    13,    16,    55,    55,
      88,    89,    93,    99,    94,    55,    91,    99,    55,     9,
      14,     8,    17,    18,    19,    20,    95,    96,    55,    55,
      55,    55,    13,    15,    96
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    91,
      93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    71,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    76,    76,    77,    77,    77,    78,    78,    78,
      80,    79,    81,    81,    82,    82,    82,    83,    83,    85,
      84,    86,    86,    87,    87,    87,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    94,
      93,    95,    95,    95,    96,    96,    96,    96,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    99,    99,
      99,    99,    99,    99,    99,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   103,   103,   103,   104,   104,
     105,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   112,   112,   113,   114,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   118,   119,   120,   121,   121,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   130,
     131,   131,   132,   133,   133,   134,   135,   136,   136,   137,
     138,   138
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     2,     2,     3,     1,     1,     1,     1,     1,
       1,     5,     2,     3,     3,     3,     3,     3,     3,    10,
       0,     6,     2,     3,     4,     3,     3,     1,     2,     0,
       6,     2,     3,     4,     3,     3,     4,     3,     3,     0,
       1,     1,     2,     1,     3,     3,     1,     3,     2,     0,
       5,     0,     1,     3,     2,     2,     2,     2,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     2,     2,     3,     1,     1,     2,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       2,     2,     3,     1,     1,     1,     1,     1,     4,     1,
       4,     1,     5,     1,     2,     3,     5,     1,     3,     1,
       6,     4
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"component\"", "\"task\"",
  "\"service\"", "\"codel\"", "LBRACE", "RBRACE", "SEMICOLON", "COLON",
  "LESS_THAN", "GREATER_THAN", "COMMA", "LPAREN", "RPAREN", "EQUAL", "IN",
  "OUT", "INPORT", "OUTPORT", "TRUE", "FALSE", "SHORT", "LONG", "FLOAT",
  "DOUBLE", "FIXED", "CHAR", "WCHAR", "STRING", "WSTRING", "BOOLEAN",
  "OCTET", "ANY", "VOID", "NATIVE", "ENUM", "UNION", "SWITCH", "CASE",
  "DEFAULT", "STRUCT", "SEQUENCE", "CONST", "TYPEDEF", "UNSIGNED",
  "OBJECT", "IDS", "INPUT", "OUTPUT", "\"char\"", "\"integer\"",
  "\"double\"", "\"string literal\"", "\"identifier\"", "MINUS", "PLUS",
  "SLASH", "TIMES", "MOD", "XOR", "OR", "AND", "RSHIFT", "LSHIFT", "TILDE",
  "POS", "NEG", "'['", "']'", "$accept", "start", "declarations",
  "declaration", "component_decl", "component_fields", "component_field",
  "port_decl", "task_decl", "$@1", "task_fields", "task_field",
  "task_errors_list", "service_decl", "$@2", "service_fields",
  "service_field", "identifier_list", "identifiers", "inputs", "input",
  "input_type", "codel_prototype", "$@3", "codel_fields", "codel_field",
  "const_decl", "const_type", "literal", "boolean_literal",
  "composed_literal", "literals", "type_decl", "type_spec",
  "simple_type_spec", "base_type_spec", "template_type_spec",
  "constr_type_spec", "declarators", "declarator", "simple_declarator",
  "array_declarator", "fixed_array_size", "floating_pt_type",
  "fixed_pt_type", "integer_type", "signed_int", "signed_short_int",
  "signed_long_int", "signed_long_long_int", "unsigned_int",
  "unsigned_short_int", "unsigned_long_int", "unsigned_long_long_int",
  "char_type", "wide_char_type", "boolean_type", "octet_type", "any_type",
  "string_type", "wide_string_type", "struct_type", "members", "member",
  "enum_type", "enumerators", "enumerator", "sequence_type", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        72,     0,    -1,    73,     0,    -1,    74,     9,    -1,    73,
      74,     9,    -1,    78,    -1,    75,    -1,    79,    -1,    84,
      -1,   103,    -1,    97,    -1,     3,    55,     7,    76,     8,
      -1,    77,     9,    -1,    76,    77,     9,    -1,    55,    10,
      54,    -1,    55,    10,    52,    -1,    55,    10,    55,    -1,
      19,    55,    55,    -1,    20,    55,    55,    -1,    20,    55,
      55,     7,     6,    55,    10,    93,     9,     8,    -1,    -1,
       4,    55,    80,     7,    81,     8,    -1,    82,     9,    -1,
      81,    82,     9,    -1,     6,    55,    10,    93,    -1,    55,
      10,    52,    -1,    55,    10,    83,    -1,    55,    -1,    83,
      55,    -1,    -1,     5,    55,    85,     7,    86,     8,    -1,
      87,     9,    -1,    86,    87,     9,    -1,     6,    55,    10,
      93,    -1,    49,    10,    90,    -1,    50,    10,    92,    -1,
      55,    10,    55,    88,    -1,    55,    10,    54,    -1,    55,
      10,    52,    -1,    -1,    89,    -1,    55,    -1,    89,    55,
      -1,    91,    -1,    90,    13,    91,    -1,    92,    16,    99,
      -1,    92,    -1,    48,    10,    55,    -1,   104,    55,    -1,
      -1,    55,    94,    14,    95,    15,    -1,    -1,    96,    -1,
      95,    13,    96,    -1,    17,    55,    -1,    18,    55,    -1,
      19,    55,    -1,    20,    55,    -1,    44,    98,    55,    16,
      99,    -1,   116,    -1,   125,    -1,   126,    -1,   127,    -1,
     114,    -1,   130,    -1,   131,    -1,   115,    -1,   128,    -1,
      52,    -1,    53,    -1,    54,    -1,    51,    -1,   100,    -1,
      55,    -1,     7,   102,     8,    -1,    14,    99,    15,    -1,
     101,    -1,    21,    -1,    22,    -1,    56,    99,    -1,    57,
      99,    -1,    66,    99,    -1,    99,    57,    99,    -1,    99,
      56,    99,    -1,    99,    59,    99,    -1,    99,    58,    99,
      -1,    99,    60,    99,    -1,    99,    63,    99,    -1,    99,
      62,    99,    -1,    99,    61,    99,    -1,    99,    65,    99,
      -1,    99,    64,    99,    -1,    99,    -1,   102,    13,    99,
      -1,    45,   104,   109,    -1,   132,    -1,   135,    -1,    36,
     103,    -1,   105,    -1,   108,    -1,   106,    -1,   107,    -1,
      55,    -1,   114,    -1,   116,    -1,   125,    -1,   126,    -1,
     127,    -1,   128,    -1,   129,    -1,   138,    -1,   130,    -1,
     131,    -1,   115,    -1,   132,    -1,   135,    -1,   110,    -1,
     109,    13,   110,    -1,   111,    -1,   112,    -1,    55,    -1,
     111,   113,    -1,   112,   113,    -1,    69,    52,    70,    -1,
      25,    -1,    26,    -1,    24,    26,    -1,    27,    11,    52,
      13,    52,    12,    -1,    27,    -1,   117,    -1,   121,    -1,
     118,    -1,   119,    -1,   120,    -1,    23,    -1,    24,    -1,
      24,    24,    -1,   122,    -1,   123,    -1,   124,    -1,    46,
      23,    -1,    46,    24,    -1,    46,    24,    24,    -1,    28,
      -1,    29,    -1,    32,    -1,    33,    -1,    34,    -1,    30,
      11,    52,    12,    -1,    30,    -1,    31,    11,    52,    12,
      -1,    31,    -1,    42,    55,     7,   133,     8,    -1,   134,
      -1,   133,   134,    -1,   104,   109,     9,    -1,    37,    55,
       7,   136,     8,    -1,   137,    -1,   136,    13,   137,    -1,
      55,    -1,    43,    11,   105,    13,    52,    12,    -1,    43,
      11,   105,    12,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    13,    15,    17,    19,    21,
      23,    25,    31,    34,    38,    42,    46,    50,    54,    58,
      69,    70,    77,    80,    84,    89,    93,    97,    99,   102,
     103,   110,   113,   117,   122,   126,   130,   135,   139,   143,
     144,   146,   148,   151,   153,   157,   161,   163,   167,   170,
     171,   177,   178,   180,   184,   187,   190,   193,   196,   202,
     204,   206,   208,   210,   212,   214,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   236,   240,   242,   244,   246,
     249,   252,   255,   259,   263,   267,   271,   275,   279,   283,
     287,   291,   295,   297,   301,   305,   307,   309,   312,   314,
     316,   318,   320,   322,   324,   326,   328,   330,   332,   334,
     336,   338,   340,   342,   344,   346,   348,   350,   354,   356,
     358,   360,   363,   366,   370,   372,   374,   377,   384,   386,
     388,   390,   392,   394,   396,   398,   400,   403,   405,   407,
     409,   412,   415,   419,   421,   423,   425,   427,   429,   434,
     436,   441,   443,   449,   451,   454,   458,   464,   466,   470,
     472,   479
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   232,   232,   235,   236,   241,   243,   245,   247,   249,
     253,   260,   266,   267,   272,   283,   291,   311,   321,   331,
     352,   351,   362,   363,   367,   371,   388,   397,   401,   410,
     409,   420,   421,   425,   429,   432,   436,   481,   491,   496,
     499,   505,   509,   515,   517,   521,   526,   532,   546,   559,
     558,   570,   571,   573,   577,   588,   599,   603,   611,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   631,   635,
     639,   643,   647,   651,   656,   660,   664,   668,   672,   679,
     685,   689,   696,   703,   710,   717,   724,   731,   738,   745,
     752,   759,   768,   774,   783,   788,   790,   791,   806,   810,
     816,   817,   818,   829,   830,   831,   832,   833,   834,   835,
     841,   842,   843,   844,   848,   850,   854,   860,   872,   873,
     877,   884,   889,   896,   905,   906,   907,   911,   916,   920,
     921,   925,   926,   927,   931,   935,   939,   943,   944,   945,
     949,   953,   957,   961,   965,   969,   973,   977,   985,   990,
     996,  1001,  1011,  1025,  1027,  1031,  1117,  1131,  1132,  1136,
    1150,  1155
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 340;
  const int Parser::yynnts_ = 68;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 81;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 71;

  const unsigned int Parser::yyuser_token_number_max_ = 323;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // G3nom

/* Line 1054 of lalr1.cc  */
#line 2593 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 1161 "/home/ccpasteur/work/git/g3nom/parsers/genom/parser.yy"
 /*** Additional Code ***/

void G3nom::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}


