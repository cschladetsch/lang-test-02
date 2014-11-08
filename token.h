
#pragma once

#include "core.h"

#include "slice.h"

struct Lexer;

// A token in the language
struct Token
{
	enum Type
	{
		None,
		Whitespace,
		Semi,
		Int,
		Float,
		String,
		True,
		False,
		Return,
		Ident,
		Dot,
		Comma,
		If,
		Else,
		For,
		While,
		OpenBrace,
		CloseBrace,
		OpenParan,
		CloseParan,
		Plus, Minus, Mul, Divide,
		Assign,
		Less, Equiv, NotEquiv, Greater, LessEquiv, GreaterEqiv,

		Not, And, Or, Xor,

		OpenSquareBracket, CloseSquareBracket,
		Increment, Decrement,
		BitAnd, BitOr, BitXor,

		Self,
		Lookup,

		Tab,
		NewLine,
		
		Fun,

		Comment,

		Yield,
		
		Suspend, Replace, Resume,
		PlusAssign, MinusAssign, MulAssign, DivAssign,
		In, Colon,
		Assert,

	};

	static const char *ToString(Type t);

	Type type;
	const Lexer *lexer;
	Slice slice;
	int lineNumber;

	Token() : lexer(0), type(None) { }
	Token(Type type, const Lexer &lexer, int lineNumber, Slice slice);

	std::string Text() const;
	char operator[](int n) const;

	friend std::ostream &operator<<(std::ostream &out, Token const &node);
};
