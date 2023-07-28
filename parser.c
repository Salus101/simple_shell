#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 * @info: Pointer to the info_t struct.
 * @path: Path to the file to check.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dup_chars - Duplicates characters from a string within a given range.
 * @pathstr: The PATH string to duplicate characters from.
 * @start: Starting index of the range.
 * @stop: Stopping index of the range.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info_t struct.
 * @pathstr: The PATH string to search in.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_cmd(info, path))
                return (path);
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}