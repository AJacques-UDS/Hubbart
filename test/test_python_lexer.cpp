#define CATCH_CONFIG_MAIN

#include <list>
#include <string>

#include "catch/catch.hpp"
#include "lexer_exception.hpp"
#include "python_token.hpp"
#include "python_lexer.hpp"

TEST_CASE("Testing data structure token", "[getLexeme, getType]") {
    PythonToken token(FROM_TOKEN, "from");

    REQUIRE(token.getLexeme() == "from");
    REQUIRE(token.getType() == FROM_TOKEN);
}

TEST_CASE("Testing the extraction of alphanumrical lexemes", "[next_alpha]") {
    std::string code = "from Hubbart import sqr2t";
    PythonLexer lexer(code);
    size_t cursor = 0;
    size_t frame = 0;

    REQUIRE(lexer.nextAlpha(&cursor, &frame) == true);
    
    std::string lex = code.substr(cursor, frame - cursor);

    REQUIRE(lex == "from");

    cursor = 5;
    frame = 5;

    REQUIRE(lexer.nextAlpha(&cursor, &frame) == true);

    lex = code.substr(cursor, frame - cursor);

    REQUIRE(lex == "Hubbart");

    cursor = 12;
    frame = 12;

    REQUIRE(lexer.nextAlpha(&cursor, &frame) == false);

    cursor = 12;
    frame = 13;

    REQUIRE(lexer.nextAlpha(&cursor, &frame) == false);
}

TEST_CASE("Testing the extract of lexemes", "[extract]") {
    std::string code = "from Hubbart import sqr2t";
    PythonLexer lexer(code);

    size_t cursor = 0;
    size_t frame = 4;

    REQUIRE(lexer.extract(&cursor, &frame) == "from");

    cursor = 1;
    frame = 0;

    REQUIRE_THROWS_AS(lexer.extract(&cursor, &frame), LexerException);
}

TEST_CASE("Adding new alphanumerical into the token's list.", "[addAlpha]") {
    std::string code = "from Hubbart import sqr2t";
    PythonLexer lexer(code);

    REQUIRE(lexer.addAlpha("from") == true);
}

TEST_CASE("Testing the extraction of invisible lexemes.", "[nextInvisible]") {
    std::string code = "from Hubbart import sqr2t";
    PythonLexer lexer(code);

    size_t cursor = 4;
    size_t frame = 4;

    REQUIRE(lexer.nextInvisible(&cursor, &frame) == true);

    std::string lex = code.substr(cursor, frame - cursor);

    REQUIRE(lex == " ");
}

TEST_CASE("Testing the lexer for the simple import line.", "[lex]") {
    std::string code = "from Hubbart import sqr2t";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 7);

    PythonTokenType types[] = {
        FROM_TOKEN, SPACE_TOKEN, IDENTIFIER_TOKEN, SPACE_TOKEN, IMPORT_TOKEN, SPACE_TOKEN, IDENTIFIER_TOKEN
    };

    std::string lexemes[] = {
        "from", " ", "Hubbart", " ", "import", " ", "sqr2t"
    };

    std::list<PythonToken>::iterator it;
    size_t counter = 0;
    for (it = tokens.begin(); it != tokens.end(); ++it) {
        REQUIRE(it->getType() == types[counter]);
        REQUIRE(it->getLexeme() == lexemes[counter]);
        counter++;
    }
}

TEST_CASE("Testing newlines", "[lex]") {
    std::string code = "from Hubbart import sqr2t\nclass Point2d\n";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 12);
}

TEST_CASE("Testing newlines and indentations", "[lex]") {
    std::string code = "from Hubbart import sqr2t\nclass Point2d\n    def init\n        self y\n";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 23);
}

TEST_CASE("Testing operators", "[lex]") {
    std::string code = "from Hubbart import sqr2t\nclass Point2d\n    def init\n        self = y\n";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 25);
}

TEST_CASE("Testing with wrappers", "[lex]") {
    std::string code = "from Hubbart import sqr2t\nclass Point2d:\n    def init(self, x, y):\n        self = y\n";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 36);
}

TEST_CASE("Testing with numbers", "[lex]") {
    std::string code = "from Hubbart import sqr2t\nglobal value = 3\nglobal key = 7.19\nclass Point2d:\n    def __init__(self, x: float, y: float) -> float:\n        self.x = x\n        self.y = y\n";
    PythonLexer lexer(code);
    REQUIRE_NOTHROW(lexer.lex() == true);

    std::list<PythonToken> tokens = lexer.getTokens();
    REQUIRE(tokens.size() == 74);
}