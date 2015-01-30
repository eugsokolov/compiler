ECE 466 - Compilers

Resources
The optional text for this class is "The Dragon Book":

Aho, Alfred V., Lam, Monica S., Sethi, Ravi and Ullman, Jeffrey D.: Compilers: Principles, Techniques, and Tools.. 2nd edition. Addison-Wesley, 2006.

The first edition of the textbook is also quite workable, especially for the earlier units of this course.

Students might find the O'Reilly book on Lex and Yacc (two tools which are used to automate the front-end of the compiler) helpful. However, much of the information in this book is dated and available for free online or in the man pages, which students should absolutely read thoroughly!

The make program will prove very useful in developing the compiler. There is an O'Reilly book on make, but again for the purposes of this project, there is enough free information available online.

The definitive reference for the C language is the ISO standard. The 1999 standard introduced a number of language extensions, some of which we may chose to ignore in class. A working draft of that standard was openly available and a copy may be downloaded here.

Another recommended book is:
Harbison, Samuel P and Steele, Guy L.: C: A reference manual. 5th edition. Prentice Hall, 2006.

This is basically a regurgitation of the ISO C standard, but with better examples and explanations, and a discussion of backwards compatibility issues with ANSI C (1989 standard) and classic K&R C.

This is a graduate-level course. The student is expected to do the necessary readings and research on his or her own. Lecture notes will be posted here, but they do not comprise the entirety of the course material for which the student is responsible. The course is divided into several units, outlines of which are presented below. These units will not necessarily be confined to a single week.
Note: lecture notes are in PostScript, which can be output directly to any PostScript printer, or viewed with a free viewer such as ghostscript. Assignments may be in text or PostScript form.
Unit 1 - Intro/Lexical
Topics include: overview of the compilation process, front-end vs back-end, the role of lexical, syntactical and semantic analysis, regular expressions, finite automata construction, lex/flex programs.
Lecture Notes (PS).
Suggested readings and activities

* Read the documentation for flex. Try out some examples.
* Read section 6.4 (Lexical Elements) of the C language standard. And/or read Chapter 2 of Harbison and Steele.
* Read Chapter 3 of the dragon book. Don't bother reading chapters 1 and 2; they will just confuse you.
Assignment 1 - Lexer
The first assignment is to write the lexical analysis phase of the C compiler. To stay on track, this should be completed by 2/13.
Assignment worksheet (PS format)
Support Files
Unit 2 - Syntactical Analysis (Parsing)
Topics: context-free grammars, derivations and parse trees, LL and LR grammars, top-down and bottom-up parsing, overview of yacc/bison. Ambiguous and non-LALR grammars and resolution, precedence/associativity. Embedded semantic actions, synthesized vs inherited attributes.
Suggested study

* Read the entire Bison manual.
* Read Chapters 4 and 5 of the Dragon Book.
* Read Chapter 7 (Expressions) in H&S. And/or read section 6.5 of the C standard.
Unit 3 -- Error handling and memory allocation

Topics: Errors vs warnings, error recovery, error reporting, memory allocation strategies within the compiler.
Unit 4 -- Semantic Analysis

Topics: compile-time vs run-time, syntax-directed translation, abstract syntax trees, type systems, symbol tables and scoping rules, feedback between lexer, parser and semantic stages, overview of C language type and namespace issues.
Suggested Readings

* Sections 6.2 and 6.7 of the C language standard.
* H & S, chapters 4 and 5.
Unit 5 -- Intermediate Representations

Unit 6 -- X86 and SPARC targets

Two potential target architectures, one CISC, one RISC, will be examined in detail. In particular, we will focus on register usage and subroutine linkage/calling conventions.
Unit 7 -- Target Code Generation

Unit 8 -- Optimization
