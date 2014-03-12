
#include "token.hpp"

#include <array>

#ifdef _MSC_VER
#include <sstream>
#include <Windows.h>
#endif

using namespace std;

string Token::token_str(Type type) {
	// This would work better if MSVC's compiler wasn't so behind on C++11.
	// Support for constexpr and static_assert is sketchy on a good day.
#ifdef _MSC_VER
	// Writing this made me die a little inside.
	#define constexpr const
#endif
	// We can't use string here because constexpr requires PODs, like char*.
	// Elements not explicitly initialized here are default-initialized.
	// For const char*s, that's nullptr and that's what we check in the assert.
	auto itype = static_cast<unsigned>(type);
	constexpr auto iTypeCount = static_cast<unsigned>(Type::Count);
	constexpr array<const char*, iTypeCount> lookup = { {
		"Error",
		"Number",
		"Identifier",
		"EoF",
	} };
#ifdef _MSC_VER
	// Cover your eyes, kids.
	auto res = lookup.at(itype);
	// std::string doesn't handle nullptr well.
	if (res != nullptr) {
		return res;
	}
#else
	static_assert(lookup[iTypeCount - 1] != nullptr,
		"Token::Type->string lookup array is missing elements. "
		"Make sure anything you added to Token::Type is mirrored here!");
	return lookup[itype];
#endif
}

Token::operator bool() {
	return type != Type::EoF;
}

ostream& operator<<(ostream& os, const Token& tok) {
	return os << " (" << Token::token_str(tok.type) << ", \"" << tok.value << "\")";
}
