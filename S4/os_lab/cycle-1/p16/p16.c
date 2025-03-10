/* Athul Anoop
 * Roll no: 25
 * Description: C program
 */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_mode_t.h>
#include <sys/dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char *extract_ft(mode_t mode);

int main(int argc, char **argv) {
  char *path = argc > 1 ? argv[1] : ".";
  DIR *dir = opendir(path);
  if (dir == NULL) {
    printf("opendir failed on path %s", path);
    exit(1);
  }
  struct dirent *entry;
  printf("\nPermissions\t UID\t Filename\t\t atime\t\t\t ctime");
  while ((entry = readdir(dir)) != NULL) {
    struct stat st = {};
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    stat(full_path, &st);

    time_t t;
    struct tm *time = localtime(&st.st_atimespec.tv_sec);

    char atime[1024];
    strftime(atime, sizeof(atime), "%Y-%m-%d %H:%M:%S", time);

    time = localtime(&st.st_ctimespec.tv_sec);
    char ctime[1024];
    strftime(ctime, sizeof(atime), "%Y-%m-%d %H:%M:%S", time);

    printf("\n%s\t %d\t %s\t\t\t %s\t %s", extract_ft(st.st_mode), st.st_uid,
           entry->d_name, atime, ctime);
  }
  closedir(dir);

  return 0;
}

char *extract_ft(mode_t mode) {

  char *perms = calloc(11, sizeof(char));
  strcat(perms, "-----------");

  // File type
  if (S_ISDIR(mode))
    perms[0] = 'd'; // Directory
  else if (S_ISLNK(mode))
    perms[0] = 'l'; // Symbolic link
  else if (S_ISREG(mode))
    perms[0] = '-'; // Regular file

  // User permissions
  if (mode & S_IRUSR)
    perms[1] = 'r';
  if (mode & S_IWUSR)
    perms[2] = 'w';
  if (mode & S_IXUSR)
    perms[3] = 'x';

  // Group permissions
  if (mode & S_IRGRP)
    perms[4] = 'r';
  if (mode & S_IWGRP)
    perms[5] = 'w';
  if (mode & S_IXGRP)
    perms[6] = 'x';

  // Others permissions
  if (mode & S_IROTH)
    perms[7] = 'r';
  if (mode & S_IWOTH)
    perms[8] = 'w';
  if (mode & S_IXOTH)
    perms[9] = 'x';
  return perms;
}
