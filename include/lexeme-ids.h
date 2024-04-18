#ifndef LEXEME_IDS_H_
#define LEXEME_IDS_H_

/**
 *auto	else	long	switch
break	enum	register	typedef
case	extern	return	union
char	float	short	unsigned
const	for	signed	void
continue	goto	sizeof	volatile
default	if	static	while
do	int	struct	_Packed
double
 */
typedef enum _lexeme_ids {
    // Reserved Keywords
    AUTO = 0x100,           // auto 
    ELSE,                   // else
    LONG,                   // long
    SWITCH,                 // switch
    BREAK,                  // break
    ENUM,                   // enum
    REGISTER,               // register
    TYPEDEF,                // typedef
    CASE,                   // case
    EXTERN,                 // extern
    RETURN,                 // return
    UNION,                  // union
    CHAR,                   // char
    FLOAT,                  // float
    SHORT,                  // short
    UNSIGNED,               // unsigned
    CONST,                  // const
    FOR,                    // for
    SIGNED,                 // signed
    VOID,                   // void
    CONTINUE,               // continue
    GOTO,                   // goto
    SIZEOF,                 // sizeof
    VOLATILE,               // volatile
    DEFAULT,                // default
    IF,                     // if
    STATIC,                 // static
    WHILE,                  // while
    DO,                     // do
    INT,                    // int
    STRUCT,                 // struct
    _PACKED,                // _Packed
    DOUBLE,                 // double
    // Operands
    LEFT_PARENTHESIS,       // (
    RIGHT_PARENTHESIS,      // )
    LEFT_BRACKET,           // [
    RIGHT_BRACKER,          // ]
    LEFT_BRACE,             // {
    RIGHT_BRACE,            // }
    DOT,                    // .
    ARROW,                  // ->
    INCREMENT,              // ++
    DECREMENT,              // --
    HYPHEN,                 // - ( subtract )
    PLUS,                   // +
    EXCLAMATION,            // !
    TILDE,                  // ~
    AMPERSAND,
    DEREFERENCE,
    MULTIPLACATION,
    DIVISION,
    PERCENT,
    BITWISE_LEFT_SHIFT,
    BITWISE_RIGHT_SHIFT,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,
    EQUALITY,
    NOT_EQUAL_TO,
    LOGICAL_AND,
    EXCLUSIVE_OR,
    INCLUSIVE_OR,
    LOGICAL_AND,
    LOGICAL_OR,
    EQUAL_TO,
    PLUS_EQUALS,
    MINUS_EQUALS,
} lexemeIds;
#endif // LEXEME_IDS_H_
