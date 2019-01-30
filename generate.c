#include <stdio.h>
#include <string.h>

FILE *out_file = NULL;
FILE *in_file = NULL;

#define SIZE_LINE_BUFFER (int)(256)

typedef enum State {
    STATE_CONSUME,
    STATE_BEGIN_ROW,
    NUM_STATES
} State;

char *state_name[NUM_STATES] = {
    [STATE_CONSUME] = "state_consume",
    [STATE_BEGIN_ROW] = "state_begin_row",
};

typedef enum Token {
    TOKEN_NEW_LINE,
    TOKEN_COMMENT,
    TOKEN_SEPARATOR,
    NUM_TOKENS
} Token;

char token_name[NUM_TOKENS] = {
    [TOKEN_COMMENT] = '#',
    [TOKEN_NEW_LINE] = '\n',
    [TOKEN_SEPARATOR] = ';'
};

typedef enum Tag {
    TAG_BEGIN_COL,
    TAG_END_COL,
    TAG_BEGIN_ROW,
    TAG_END_ROW,
    TAG_BEGIN_TABLE,
    TAG_END_TABLE,
    TAG_BEGIN_TBODY,
    TAG_END_TBODY,
    NUM_TAGS
} Tag;

char *tag_name[NUM_TAGS] = {
    [TAG_BEGIN_COL] = "<td>",
    [TAG_END_COL] = "</td>",
    [TAG_BEGIN_ROW] = "<tr>",
    [TAG_END_ROW] = "</tr>",
    [TAG_BEGIN_TABLE] = "<table>",
    [TAG_END_TABLE] = "</table>",
    [TAG_BEGIN_TBODY] = "<tbody>",
    [TAG_END_TBODY] = "</tbody>"
};

int is_token(char c, Token type)
{
    return token_name[type] == c;
}

void create_table_headers(void)
{
    fprintf(out_file,
        "<thead>\n"
        "<tr id=\"header-item\">\n"
        "    <th id=\"watched\">Watched</th>\n"
        "    <th id=\"title\">Title</th>\n"
        "    <th id=\"director\">Director</th>\n"
        "    <th id=\"year\">Year</th>\n"
        "</tr>\n"
        "</thead>\n"
    );
}

void create_tag(Tag type)
{
    if (type == TAG_BEGIN_COL)
        fprintf(out_file, "    %s", tag_name[type]);
    else
        fprintf(out_file, "%s\n", tag_name[type]);
}

#define next() (c = fgetc(in_file))

int main(void)
{
    char c = '\0';
    int state = STATE_BEGIN_ROW;

    in_file = stdin;
    out_file = fopen("film-list.html", "w");

    create_tag(TAG_BEGIN_TABLE);
    create_table_headers();
    create_tag(TAG_BEGIN_TBODY);
    next();

    while(c != EOF)
    {
        switch (state)
        {
        case STATE_BEGIN_ROW:
            if (is_token(c, TOKEN_COMMENT))
            {
                while (c != '\n')
                    next();
                next();
            }
            else if (c == ' ' || c == '\n')
                next();
            else
            {
                create_tag(TAG_BEGIN_ROW);
                create_tag(TAG_BEGIN_COL);
                state = STATE_CONSUME;
            }
            break;

        case STATE_CONSUME:
            if (is_token(c, TOKEN_SEPARATOR))
            {
                next();
                /* Trim LHS whitespace */
                if (c == ' ')
                    next();
                create_tag(TAG_END_COL);
                create_tag(TAG_BEGIN_COL);
            }
            else if (c == '\n')
            {
                next();
                create_tag(TAG_END_COL);
                create_tag(TAG_END_ROW);
                state = STATE_BEGIN_ROW;
            }
            else
            {
                fprintf(out_file, "%c", c);
                next();
            }
            break;
        }
    }

    create_tag(TAG_END_TBODY);
    create_tag(TAG_END_TABLE);

    fclose(out_file);
    fclose(in_file);
}
