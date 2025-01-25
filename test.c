#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t new_len(const char *s, const char *ops)
{
    size_t new_len = 0;
    size_t i = 0;
    size_t j;

    while (s[i])
    {
        new_len++;
        j = 0;
        while (ops[j])
        {
            if (s[i] == ops[j])
            {
                new_len += 2;
                break;
            }
            j++;
        }
        i++;
    }
    return (new_len);
}

static int is_operator(const char c, const char *ops)
{
    size_t j = 0;
    while (ops[j])
    {
        if (c == ops[j])
        {
            return (1);
        }
        j++;
    }
    return (0);
}

static char *get_result(const char *s, const char *ops, char *result)
{
    size_t i = 0;
    size_t k = 0;

    while (s[i])
    {
        if (is_operator(s[i], ops))
        {
            result[k++] = ' ';
            result[k++] = s[i];
            result[k++] = ' ';
        }
        else
        {
            result[k++] = s[i];
        }
        i++;
    }
    result[k] = '\0';
    return (result);
}

char *pre_split(char **s, const char *ops)
{
    size_t len = new_len(*s, ops);
    char *result = malloc(len + 1);
    if (!result)
    {
        perror("malloc failed");
        return NULL;
    }
    result = get_result(*s, ops, result);
    free(*s);
    *s = NULL;
    return (result);
}

int main()
{
    char *s = strdup("ls|grep \"count\""); // Dynamically allocate `s`
    const char *ops = "|><";
    char *result = pre_split(&s, ops); // Pass `&s` to allow freeing

    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result); // Free the allocated memory for the result
    }

    return 0;
}
