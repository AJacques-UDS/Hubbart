#include <list>
#include <string>

#include "catch/catch.hpp"
#include "python_lexer.hpp"
#include "python_token_type.hpp"

TEST_CASE("Testing for keyword __init__", "[lex]") {
    std::string code = "__init__";

    PythonLexer lex(code);
    REQUIRE_NOTHROW(lex.lex() == true);

    std::list<PythonToken> tokens = lex.getTokens();
    auto item = tokens.begin();
    REQUIRE(item->getType() == PythonTokenType::INIT_TOKEN);
    REQUIRE(item->getLexeme() == "__init__");
}

TEST_CASE("Testing the keyword break", "[lex]") {
    std::string code = "break";

    PythonLexer lex(code);
    REQUIRE_NOTHROW(lex.lex() == true);

    std::list<PythonToken> tokens = lex.getTokens();
    auto item = tokens.begin();
    REQUIRE(item->getType() == PythonTokenType::BREAK_TOKEN);
    REQUIRE(item->getLexeme() == "break");
}

TEST_CASE("Testing the keyword class", "[lex]") {
    std::string code = "class";

    PythonLexer lex(code);
    REQUIRE_NOTHROW(lex.lex() == true);

    std::list<PythonToken> tokens = lex.getTokens();
    auto item = tokens.begin();
    REQUIRE(item->getType() == PythonTokenType::CLASS_TOKEN);
    REQUIRE(item->getLexeme() == "class");
}

TEST_CASE("Testing the keyword elif", "[lex]") {
    std::string code = "elif";

    PythonLexer lex(code);
    REQUIRE_NOTHROW(lex.lex() == true);

    std::list<PythonToken> tokens = lex.getTokens();
    auto item = tokens.begin();
    REQUIRE(item->getType() == PythonTokenType::ELIF_TOKEN);
    REQUIRE(item->getLexeme() == "elif");
}