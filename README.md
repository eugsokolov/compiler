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
Lecture Notes (PS).
Suggested study

* Read the entire Bison manual.
* Read Chapters 4 and 5 of the Dragon Book.
* Read Chapter 7 (Expressions) in H&S. And/or read section 6.5 of the C standard.

Assignment 2 - Calcuator
Using the complete lexer from assignment 1, build a rudimentary parser for a subsset of C expressions, including a primitive symbol table to hold variable values. Target completion date: Feb 26
Assignment 2 worksheet (PS format)
Unit 3 -- Error handling and memory allocation

Topics: Errors vs warnings, error recovery, error reporting, memory allocation strategies within the compiler.
Lecture Notes (PS).
Unit 4 -- Semantic Analysis

Topics: compile-time vs run-time, syntax-directed translation, abstract syntax trees, type systems, symbol tables and scoping rules, feedback between lexer, parser and semantic stages, overview of C language type and namespace issues.
Lecture Notes (PS).
Suggested Readings

* Sections 6.2 and 6.7 of the C language standard.
* H & S, chapters 4 and 5.
Assignment 3 - Declarations
Parse C declarations and construct AST representations of types. Additional symbol table stuff. assign3.txt
Unit 5 -- Intermediate Representations

Graphical vs linear IR, internal vs external IR. 1-address and 3-address linear IRs. Overview of IR approaches of popular languages including Perl, Python, Java, PHP. Overview of LLVM IR. Techniques for generating IR from AST.

Lecture Notes (PS).
Assignment 4 - Complete AST
Parse entire C language (specific restricted subset thereof) and generate AST representation of declarations, expressions and control constructs. assign4.txt
Assignment 5 - IR Generation
Generate linear IR from AST. assign5.txt
Unit 6 -- X86 and SPARC targets

Two potential target architectures, one CISC, one RISC, will be examined in detail. In particular, we will focus on register usage and subroutine linkage/calling conventions.
Lecture Notes (PS).
Unit 7 -- Target Code Generation


Lecture Notes (PS).
Unit 8 -- Optimization

Lecture Notes (PS).
Assignment 6 - Target Code Generation
This is the last assignment!
assign6.txt

Here are some resources to help you complete this assignment:
Intel IA-32 ref manual volume 1: basic architecture, addressing modes.
Intel IA-32 instruction set reference for opcodes beginning with the letter A-M.
Intel IA-32 instruction set reference for opcodes beginning with the letter N-Z. Note that the instruction set is presented according to Intel syntax, which differs from the "UNIX" or "AT&T" syntax which is used on Solaris, Linux and BSD systems.
Sun Microsystems x86 Assembly Language Reference This booklet presents an overview of the X86 assembler in UNIX notation and provides a translation of opcode names and addressing mode nomenclature between UNIX and Intel formats. It does not describe the individual instructions in detail
SPARC Assembly Reference Manual Provides an overview of the SPARC V8 and V9 assemblers. Doesn't give a detailed explanation of each instruction but there is a summary of all instructions and addressing modes
SPARC Architecture Manual Provides detailed coverage of the SPARC V9 architecture including operation of the processor, register windowing, addressing modes, opcodes and instruction formats. This manual was written by the SPARC International group and as such is OS and assembler agnostic. But unlike the Intel reference manuals, the notation used follows the UNIX standard very closely.
