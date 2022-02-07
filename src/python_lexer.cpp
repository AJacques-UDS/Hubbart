#include "python_lexer.hpp"

static std::map<char, PythonTokenType> wrappers = {
    {'(', PythonTokenType::LEFT_PAREN_TOKEN},
    {'[', PythonTokenType::LEFT_SQUARE_BRACK_TOKEN},
    {'{', PythonTokenType::LEFT_CURLY_BRACK_TOKEN},
    {'}', PythonTokenType::RIGHT_CURLY_BRACK_TOKEN},
    {']', PythonTokenType::RIGHT_SQUARE_BRACK_TOKEN},
    {')', PythonTokenType::RIGHT_PAREN_TOKEN}
};

static std::map<std::string, PythonTokenType> operators = {
    {"=", PythonTokenType::ASSIGN_TOKEN},
    {"==", PythonTokenType::EQUAL_TOKEN},
    {"!=", PythonTokenType::NOT_EQUAL_TOKEN},
    {">", PythonTokenType::GREATER_THAN_TOKEN},
    {">=", PythonTokenType::GREATER_OR_EQUAL_TOKEN},
    {">>", PythonTokenType::SHIFT_RIGHT_TOKEN},
    {"<", PythonTokenType::SMALLER_THAN_TOKEN},
    {"<=", PythonTokenType::SMALLER_OR_EQUAN_TOKEN},
    {"<<", PythonTokenType::SHIFT_LEFT_TOKEN},
    {"+", PythonTokenType::ADD_TOKEN},
    {"-", PythonTokenType::SUB_TOKEN},
    {"->", PythonTokenType::ARROW_TOKEN},
    {"*", PythonTokenType::MUL_TOKEN},
    {"/", PythonTokenType::DIV_TOKEN},
    {"**", PythonTokenType::POW_TOKEN},
    {"+=", PythonTokenType::ACC_ADD_TOKEN},
    {"-=", PythonTokenType::ACC_SUB_TOKEN},
    {"*=", PythonTokenType::ACC_MUL_TOKEN},
    {"/=", PythonTokenType::ACC_DIV_TOKEN},
    {"&", PythonTokenType::AMP_TOKEN},
    {"|", PythonTokenType::PIPE_TOKEN},
    {"^", PythonTokenType::XOR_TOKEN},
    {"~", PythonTokenType::TILDE_TOKEN},
    {".", PythonTokenType::DOT_TOKEN},
    {",", PythonTokenType::COMMA_TOKEN},
    {";", PythonTokenType::SEMICOLON_TOKEN},
    {":", PythonTokenType::COLON_TOKEN}
};

static std::map<std::string, PythonTokenType> reserved = {
    {"and", AND_TOKEN},
    {"bool", BOOL_TOKEN},
    {"break", BREAK_TOKEN},
    {"bytes", BYTES_TOKEN},
    {"class", CLASS_TOKEN},
    {"def", DEF_TOKEN},
    {"elif", ELIF_TOKEN},
    {"else", ELSE_TOKEN},
    {"False", FALSE_TOKEN},
    {"for", FOR_TOKEN},
    {"from", FROM_TOKEN},
    {"global", GLOBAL_TOKEN},
    {"if", IF_TOKEN},
    {"in", IN_TOKEN},
    {"int", INT_TOKEN},
    {"import", IMPORT_TOKEN},
    {"not", NOT_TOKEN},
    {"None", NONE_TOKEN},
    {"or", OR_TOKEN},
    {"return", RETURN_TOKEN},
    {"self", SELF_TOKEN},
    {"set", SET_TOKEN},
    {"True", TRUE_TOKEN},
    {"tuple", TUPLE_TOKEN},
    {"while", WHILE_TOKEN},
    {"with", WITH_TOKEN}
};

static bool iswrapper(const char &chr) {
    return wrappers.find(chr) != wrappers.end();
}

static bool isoperator(const std::string &str) {
    return operators.find(str) != operators.end();
}

PythonLexer::PythonLexer(const std::string &src) {
    this->source = src;
}

bool PythonLexer::lex(void) {
    size_t cursor = 0;
    size_t frame = 0;
    bool end = false;

    while (!end) {
        char chr = this->source[cursor];
        std::string str(2, chr);

        if (isalpha(chr)) {
            if (this->nextAlpha(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addAlpha(lex)) throw LexerException("Can't add alphanumerical into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next alphanumerical.");
            }
            this->startOfLine = false;
        } else if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r') {
            if (this->nextInvisible(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addInvisible(lex)) throw LexerException("Can't add invisible into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next invisible.");
            }
        } else if (chr == '\0') {
            end = true;
        }
    }

    return true;
}

bool PythonLexer::nextAlpha(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;

    char current = this->source[*frame];
    if (isalpha(current)) {
        *frame = *frame + 1;
        current = this->source[*frame];
        while (isalnum(current) || current == '_') {
            *frame = *frame + 1;
            current = this->source[*frame];
        }
        return true;
    } else {
        return false;
    }
}

bool PythonLexer::nextInvisible(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;

    char chr = this->source[*frame];
    while (chr == ' ') {
        *frame = *frame + 1;
        chr = this->source[*frame];
    }

    return true;
}

std::string PythonLexer::extract(size_t* cursor, size_t* frame) {
    if (*cursor == *frame) return "";
    else if(*cursor < *frame) {
        std::string result = this->source.substr(*cursor, *frame - *cursor);
        *cursor = *frame;
        return result;
    } else {
        throw LexerException("Can't extract - cursor ahead of frame.");
    }
}
    
bool PythonLexer::addAlpha(const std::string &lex) {
    PythonTokenType t;

    if (reserved.find(lex) != reserved.end()) {
        t = reserved[lex];
    } else {
        t = IDENTIFIER_TOKEN;
    }

    PythonToken tok(t, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

bool PythonLexer::addInvisible(const std::string &lex) {
    PythonToken tok(SPACE_TOKEN, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}


std::list<PythonToken> PythonLexer::getTokens(void) {
    return this->tokens;
}