#include "lt_lexer.h"

#include <stdbool.h>
#include <string.h>

void lt_lexer_init(struct lt_lexer *lexer, const char *source)
{
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
}

static size_t get_token_length(struct lt_lexer *lexer);

static struct lt_token make_token(struct lt_lexer *lexer, enum lt_token_type type);
static struct lt_token make_eof_token(struct lt_lexer *lexer);
static struct lt_token make_err_token(struct lt_lexer *lexer, const char *message);

static bool is_at_eof(struct lt_lexer *lexer);
static bool is_at_eol(struct lt_lexer *lexer);

static bool is_alpha(char c);
static bool is_digit(char c);
static bool is_whitespace(char c);

static void move_to_current(struct lt_lexer *lexer);
static char advance(struct lt_lexer *lexer);
static char peek(struct lt_lexer *lexer);
static char peek_next(struct lt_lexer *lexer);
static bool match(struct lt_lexer *lexer, char expected);

static void skip_comment(struct lt_lexer *lexer);
static void skip_insignificant(struct lt_lexer *lexer);

static struct lt_token scan_number(struct lt_lexer *lexer);
static struct lt_token scan_string(struct lt_lexer *lexer);
static struct lt_token scan_identifier(struct lt_lexer *lexer);

static enum lt_token_type check_keyword(struct lt_lexer *lexer, size_t offset, char *keyword, enum lt_token_type type);
static enum lt_token_type classify_identifier(struct lt_lexer *lexer);

struct lt_token lt_lexer_next(struct lt_lexer *lexer)
{
    skip_insignificant(lexer);
    move_to_current(lexer);

    if (is_at_eof(lexer)) {
        return make_eof_token(lexer);
    }

    char c = advance(lexer);

    if (is_alpha(c)) {
        return scan_identifier(lexer);
    }

    if (is_digit(c)) {
        return scan_number(lexer);
    }

    switch (c) {
        case ('('):
            return make_token(lexer, LT_TOKEN_L_PAREN);
        case (')'):
            return make_token(lexer, LT_TOKEN_R_PAREN);
        case ('{'):
            return make_token(lexer, LT_TOKEN_L_BRACE);
        case ('}'):
            return make_token(lexer, LT_TOKEN_R_BRACE);
        case ('['):
            return make_token(lexer, LT_TOKEN_L_BRACKET);
        case (']'):
            return make_token(lexer, LT_TOKEN_R_BRACKET);
        case ('.'):
            return make_token(lexer, LT_TOKEN_DOT);
        case (','):
            return make_token(lexer, LT_TOKEN_COMMA);
        case (':'):
            return make_token(lexer, LT_TOKEN_COLON);
        case ('+'):
            return make_token(lexer, LT_TOKEN_PLUS);
        case ('-'):
            return make_token(lexer, LT_TOKEN_MINUS);
        case ('*'):
            return make_token(lexer, LT_TOKEN_STAR);
        case ('/'):
            return make_token(lexer, LT_TOKEN_SLASH);
        case ('>'):
            return make_token(lexer, match(lexer, '=') ? LT_TOKEN_GREATER_EQUAL : LT_TOKEN_GREATER);
        case ('<'): {
            if (match(lexer, '=')) {
                return make_token(lexer, LT_TOKEN_LESS_EQUAL);
            }

            if (match(lexer, '|')) {
                return make_token(lexer, LT_TOKEN_L_PIPE);
            }

            return make_token(lexer, LT_TOKEN_LESS);
        }
        case '|': {
            if (match(lexer, '|')) {
                return make_token(lexer, LT_TOKEN_OR);
            }

            if (match(lexer, '>')) {
                return make_token(lexer, LT_TOKEN_R_PIPE);
            }

            break;
        }
        case '&': {
            if (match(lexer, '&')) {
                return make_token(lexer, LT_TOKEN_AND);
            }

            break;
        }
        case '"':
            return scan_string(lexer);
        default:
            break;
    }

    return make_err_token(lexer, "Unexpected character");
}

static size_t get_token_length(struct lt_lexer *lexer)
{
    return lexer->current - lexer->start;
}

static struct lt_token make_token(struct lt_lexer *lexer, enum lt_token_type type)
{
    struct lt_token token = {
        .type = type,
        .start = lexer->start,
        .length = get_token_length(lexer),
        .line = lexer->line,
    };

    return token;
}

static struct lt_token make_eof_token(struct lt_lexer *lexer)
{
    return make_token(lexer, LT_TOKEN_EOF);
}

static struct lt_token make_err_token(struct lt_lexer *lexer, const char *message)
{
    struct lt_token token = {
        .type = LT_TOKEN_ERR,
        .start = message,
        .length = strlen(message),
        .line = lexer->line,
    };

    return token;
}

static bool is_at_eof(struct lt_lexer *lexer)
{
    return peek(lexer) == '\0';
}

static bool is_at_eol(struct lt_lexer *lexer)
{
    return peek(lexer) == '\n';
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_whitespace(char c)
{
    return c == ' ' || c == '\r' || c == '\t';
}

static void move_to_current(struct lt_lexer *lexer)
{
    lexer->start = lexer->current;
}

static char advance(struct lt_lexer *lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static char peek(struct lt_lexer *lexer)
{
    return *lexer->current;
}

static char peek_next(struct lt_lexer *lexer)
{
    if (is_at_eof(lexer)) {
        return '\0';
    }

    return lexer->current[1];
}

static bool match(struct lt_lexer *lexer, char expected)
{
    if (is_at_eof(lexer) || peek(lexer) != expected) {
        return false;
    }

    advance(lexer);
    return true;
}

static void skip_comment(struct lt_lexer *lexer)
{
    while (!is_at_eol(lexer) && !is_at_eof(lexer)) {
        advance(lexer);
    }
}

static void skip_insignificant(struct lt_lexer *lexer)
{
    for (;;) {
        char c = peek(lexer);
        if (!is_whitespace(c)) {
            if (c == '/' && peek_next(lexer)) {
                skip_comment(lexer);
                continue;
            }

            return;
        }

        advance(lexer);
    }
}

static struct lt_token scan_number(struct lt_lexer *lexer)
{
    while (is_digit(peek(lexer))) {
        advance(lexer);
    }

    if (peek(lexer) == '.' && is_digit(peek_next(lexer))) {
        advance(lexer);
        while (is_digit(peek(lexer))) {
            advance(lexer);
        }
    }

    return make_token(lexer, LT_TOKEN_NUMBER);
}

static struct lt_token scan_string(struct lt_lexer *lexer)
{
    while (peek(lexer) != '"' && !is_at_eol(lexer) && !is_at_eof(lexer)) {
        advance(lexer);
    }

    if (is_at_eol(lexer)) {
        return make_err_token(lexer, "Multiline strings not supported");
    }

    if (is_at_eof(lexer)) {
        return make_err_token(lexer, "Unterminated string literal");
    }

    advance(lexer);
    return make_token(lexer, LT_TOKEN_STRING);
}

static struct lt_token scan_identifier(struct lt_lexer *lexer)
{
    while (is_alpha(peek(lexer)) || is_digit(peek(lexer))) {
        advance(lexer);
    }

    return make_token(lexer, classify_identifier(lexer));
}

static enum lt_token_type check_keyword(struct lt_lexer *lexer, size_t offset, char *keyword, enum lt_token_type type)
{
    size_t keyword_length = strlen(keyword);
    size_t token_length = get_token_length(lexer);
    bool is_length_same = token_length == keyword_length;
    if (is_length_same && memcmp(lexer->start + offset, keyword + offset, keyword_length) == 0) {
        return type;
    }

    return LT_TOKEN_IDENTIFIER;
}

static enum lt_token_type classify_identifier(struct lt_lexer *lexer)
{
    size_t length = get_token_length(lexer);
    switch (lexer->start[0]) {
        case 'e':
            return check_keyword(lexer, 1, "else", LT_TOKEN_KEY_ELSE);
        case 'f':
            if (length > 1) {
                switch (lexer->start[1]) {
                    case 'a':
                        return check_keyword(lexer, 2, "false", LT_TOKEN_KEY_FALSE);
                    case 'n':
                        return check_keyword(lexer, 2, "fn", LT_TOKEN_KEY_FN);
                    case 'o':
                        return check_keyword(lexer, 2, "for", LT_TOKEN_KEY_FOR);
                    default:
                        break;
                }
            }

            break;
        case 'i':
            return check_keyword(lexer, 1, "if", LT_TOKEN_KEY_IF);
        case 'l':
            return check_keyword(lexer, 1, "let", LT_TOKEN_KEY_LET);
        case 'm':
            return check_keyword(lexer, 1, "match", LT_TOKEN_KEY_MATCH);
        case 'p':
            return check_keyword(lexer, 1, "print", LT_TOKEN_KEY_PRINT);
        case 'r':
            return check_keyword(lexer, 1, "return", LT_TOKEN_KEY_RETURN);
        case 's':
            if (length > 1) {
                switch (lexer->start[1]) {
                    case 'e':
                        return check_keyword(lexer, 2, "self", LT_TOKEN_KEY_SELF);
                    case 't':
                        return check_keyword(lexer, 2, "struct", LT_TOKEN_KEY_STRUCT);
                    default:
                        break;
                }
            }

            break;
        case 't':
            return check_keyword(lexer, 1, "true", LT_TOKEN_KEY_TRUE);
        case 'w':
            if (length > 1) {
                switch (lexer->start[1]) {
                    case 'h':
                        return check_keyword(lexer, 2, "while", LT_TOKEN_KEY_WHILE);
                    case 'i':
                        return check_keyword(lexer, 2, "with", LT_TOKEN_KEY_WITH);
                    default:
                        break;
                }
            }

            break;
    }

    return LT_TOKEN_IDENTIFIER;
}
