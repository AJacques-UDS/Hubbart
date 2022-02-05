#include "python_lexer.hpp"

static std::map<std::string, PythonTokenType> reserved = {
    { "bool", BOOL_TOKEN },
    { "break", BREAK_TOKEN }, 
    { "bytes", BYTES_TOKEN }, 
    { "class", CLASS_TOKEN }, 
    { "def", DEF_TOKEN }, 
    { "elif", ELIF_TOKEN }, 
    { "else", ELSE_TOKEN }, 
    { "False", FALSE_TOKEN }, 
    { "for", FOR_TOKEN }, 
    { "from", FROM_TOKEN }, 
    { "global", GLOBAL_TOKEN }, 
    { "if", IF_TOKEN }, 
    { "in", IN_TOKEN }, 
    { "int", INT_TOKEN }, 
    { "import", IMPORT_TOKEN }, 
    { "None", NONE_TOKEN }, 
    { "return", RETURN_TOKEN }, 
    { "self", SELF_TOKEN }, 
    { "set", SET_TOKEN }, 
    { "True", TRUE_TOKEN }, 
    { "tuple", TUPLE_TOKEN }, 
    { "while", WHILE_TOKEN }, 
    { "with", WITH_TOKEN }
};

PythonToken PythonLexer::init_lexer(size_t* frame) {
    if (*frame != 0) {
        throw std::invalid_argument("Frame MUST be 0.");
    }

    size_t result = 0;

    char current = this->source[result];
    while (isblank(current)) {
        result++;
        current = this->source[result];
    }

    if (frame > 0) {
        return PythonToken(INDENTATION_TOKEN, this->source.substr(0, *frame));
    } else {
        return PythonToken(INDENTATION_TOKEN, "");
    }
}

PythonToken PythonLexer::handling_alpha(size_t *cursor, size_t *frame) {
    char current = this->source[*frame];

    if (isalpha(current) || current == '_') {
        *frame = *frame + 1;
        current = this->source[*frame];

        while (isalnum(current) || current == '_') {
            *frame = *frame + 1;
            current = this->source[*frame];
        }
        std::string lexeme = this->source.substr(*cursor, *frame - *cursor);
        if (reserved.find(lexeme) != reserved.end()) {
            return PythonToken(reserved[lexeme], lexeme);
        } else {
            return PythonToken(IDENTIFIER_TOKEN, lexeme);
        }
    } else {
        throw std::invalid_argument("Not valid.");
    }
}

PythonToken PythonLexer::handling_digit(size_t *cursor, size_t *frame) {
    char current = this->source[*frame];
    size_t len = 0;
    bool end = false;

    if (isdigit(current)) {
        while (!end) {
            *frame = *frame + 1;
            len++;
            current = this->source[*frame];
            std::string currentLexeme = this->source.substr(*cursor, len);
        }
    } else {
        throw std::invalid_argument("Not valid.");
    }
}

PythonToken PythonLexer::handling_punct(size_t *, size_t *) {

}

PythonToken PythonLexer::next_token(size_t* cursor, size_t* frame) {
    char chr = this->source[*frame];
    
    if (isalpha(chr)) {
        return handling_alpha(cursor, frame);
    } else if (isdigit(chr)) {
        return handling_digit(cursor, frame);
    } else if (isblank(chr)) {
        switch (chr) {
            case ' ':
                while (chr == ' ') {
                    *frame = *frame + 1;
                    chr = this->source[*frame];
                }
                return PythonToken(INDENTATION_TOKEN, this->source.substr(*cursor, *frame - *cursor));
            case '\t':
                while (chr == '\t') {
                    *frame = *frame + 1;
                    chr = this->source[*frame];
                }
                return PythonToken(INDENTATION_TOKEN, this->source.substr(*cursor, *frame - *cursor));
            case '\r':
            case '\n':
                while (chr == '\r' || chr == '\n') {
                    *frame = *frame + 1;
                    chr = this->source[*frame];
                }
                return PythonToken(NEWLINE_TOKEN, this->source.substr(*cursor, *frame - *cursor));
        }
    } else if (ispunct(chr)) {
        return handling_punct(cursor, frame);
    } else if (chr == '\0') {
        return PythonToken(PythonTokenType::EOF_TOKEN, this->source.substr(*cursor, 1));
    }

    throw std::out_of_range("Not valid.");
}

PythonLexer::PythonLexer(const std::string &source) {
    this->source = source;
}

void PythonLexer::lex(void) {
    size_t cursor = 0;
    size_t frame = 0;
    
    PythonToken token = init_lexer(&frame);
    this->tokens.push_back(token);
    
    cursor = frame;

    token = next_token(&cursor, &frame);
}

std::list<PythonToken> PythonLexer::getTokens(void) {
    return tokens;
}