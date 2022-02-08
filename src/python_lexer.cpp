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
    {"__init__", INIT_TOKEN},
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

static bool isoperator(const char &chr) {
    std::string str(1, chr);
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

        if (isalpha(chr) || chr == '_') {
            if (this->nextAlpha(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addAlpha(lex)) throw LexerException("Can't add alphanumerical into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next alphanumerical.");
            }
        } else if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r') {
            if (this->nextInvisible(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addInvisible(lex)) throw LexerException("Can't add invisible into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next invisible.");
            }
        } else if (chr == '\0') {
            end = true;
        } else if (isoperator(chr)) {
            if (this->nextOperator(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addOperator(lex)) throw LexerException("Can't add operator into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next operator.");
            }
        } else if (iswrapper(chr)) {
            if (this->nextWrapper(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addWrapper(lex)) throw LexerException("Can't add wrapper into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next operator.");
            }
        } else if (isdigit(chr)) {
            if (this->nextDigit(&cursor, &frame)) {
                std::string lex = this->extract(&cursor, &frame);
                if (!this->addDigit(lex)) throw LexerException("Can't add digit into tokens' list.");
            } else {
                throw LexerException("Couldn't frame the next digit.");
            }
        } else {
            spdlog::info("Shouldn't be here. (character {})", chr);            
        }
    }

    return true;
}

bool PythonLexer::nextAlpha(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;

    char current = this->source[*frame];
    if (isalpha(current) || current == '_') {
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
    char tst = chr;

    while (chr == tst) {
        // Handling indentation one at a time
        if (this->startOfLine) {
            if (this->tabLength > 0) {
                if ((*frame - *cursor) == this->tabLength) break;
            }
        }

        *frame = *frame + 1;
        chr = this->source[*frame];
    }

    return true;
}

bool PythonLexer::nextOperator(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;

    char chr = this->source[*frame];
    char tst = this->source[*frame + 1];
    std::string str(1, chr);
    str += tst;

    *frame = *frame + 1;
    if (operators.find(str) != operators.end()) {
        *frame = *frame + 1;
    }

    return true;
}

bool PythonLexer::nextWrapper(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;
    *frame = *frame + 1;
    return true;
}

bool PythonLexer::nextDigit(size_t* cursor, size_t* frame) {
    if (*cursor != *frame) return false;
    char chr = this->source[*frame];

    if (isdigit(chr)) {
        *frame = *frame + 1;
        chr = this->source[*frame];
        int points = 0;
        while (isdigit(chr) || chr == '.') {
            if (chr == '.' && points > 0) throw LexerException("Too many decimal points");
            else points++;

            *frame = *frame + 1;
            chr = this->source[*frame];
        }
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

    this->startOfLine = false;

    PythonToken tok(t, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

bool PythonLexer::addInvisible(const std::string &lex) {
    char chr = lex[0];
    PythonTokenType t;

    switch (chr) {
        case ' ':
            if (this->startOfLine == true) {
                t = PythonTokenType::INDENTATION_TOKEN;
                if (this->tabLength == 0) this->tabLength = lex.length();
            } else {
                t = PythonTokenType::SPACE_TOKEN;
                this->startOfLine = false;
            }
            break;
        case '\n':
            t = PythonTokenType::NEWLINE_TOKEN;
            this->startOfLine = true;
            break;
    }

    PythonToken tok(t, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

bool PythonLexer::addOperator(const std::string &lex) {
    PythonTokenType t = operators[lex];
    this->startOfLine = false;
    PythonToken tok(t, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

bool PythonLexer::addWrapper(const std::string &lex) {
    PythonTokenType t = wrappers[lex[0]];
    switch (lex[0]) {
    case '(':
        this->paren++;
        break;
    case '[':
        this->sbrack++;
        break;
    case '{':
        this->cbrack++;
        break;
    case ')':
        if (this->paren == 0) throw LexerException("Too many closing parenthesis.");
        this->paren--;
        break;
    case ']':
        if (this->sbrack == 0) throw LexerException("Too many closing square brackets.");
        this->paren--;
        break;
    case '}':
        if (this->cbrack == 0) throw LexerException("Too many closing curly brackets.");
        this->paren--;
        break;
    default:
        throw LexerException("Not a valid wrapper.");
    }

    PythonToken tok(t, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

bool PythonLexer::addDigit(const std::string &lex) {
    PythonToken tok(PythonTokenType::NUMBER_TOKEN, lex);
    size_t size = this->tokens.size();
    this->tokens.push_back(tok);
    return (size + 1) == this->tokens.size();
}

std::list<PythonToken> PythonLexer::getTokens(void) {
    return this->tokens;
}
