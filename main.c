#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Prototypes de tes fonctions (à adapter si besoin)
ssize_t ft_read(int fd, void *buf, size_t count);
size_t  ft_strlen(const char *s);
int     ft_strcmp(const char *s1, const char *s2);
char    *ft_strcpy(char *dest, const char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);
char *ft_strdup(const char *s);
int ft_atoi_base(const char *str, const char *base);
char *ft_strchr(const char *s, int c);

void test_strlen(void)
{
    printf("=== Test ft_strlen ===\n");
    printf("ft_strlen(\"Hello\") = %zu\n", ft_strlen("Hello"));
    printf("strlen(\"Hello\") (libc) = %zu\n", strlen("Hello"));
    printf("ft_strlen(\"\") = %zu\n", ft_strlen(""));
    printf("strlen(\"\") = %zu\n", strlen(""));
    printf("\n");
}

void test_strcmp(void)
{
    printf("=== Test ft_strcmp ===\n");
    printf("ft_strcmp(\"abc\", \"abc\") = %d\n", ft_strcmp("abc", "abc"));
    printf("strcmp(\"abc\", \"abc\") (libc) = %d\n", strcmp("abc", "abc"));
    printf("ft_strcmp(\"abc\", \"abd\") = %d\n", ft_strcmp("abc", "abd"));
    printf("strcmp(\"abc\", \"abd\") = %d\n", strcmp("abc", "abd"));
    printf("ft_strcmp(\"abd\", \"abc\") = %d\n", ft_strcmp("abd", "abc"));
    printf("strcmp(\"abd\", \"abc\") = %d\n", strcmp("abd", "abc"));
    printf("\n");
}

void test_strcpy(void)
{
    printf("=== Test ft_strcpy ===\n");
    char dest[50];
    ft_strcpy(dest, "Hello World");
    printf("Après ft_strcpy: dest = \"%s\"\n", dest);

    char dest2[50];
    strcpy(dest2, "Hello World");
    printf("Avec strcpy (libc): dest2 = \"%s\"\n", dest2);
    printf("\n");
}

void test_write(void)
{
    printf("=== Test ft_write ===\n");

    // Test sur stdout
    printf("Écriture sur stdout :\n");
    ssize_t ret1 = ft_write(1, "Hello via ft_write\n", 20);
    printf("Retour ft_write (stdout) = %zd, errno = %d\n", ret1, errno);

    // Test sur stderr
    printf("Écriture sur stderr :\n");
    ssize_t ret2 = ft_write(2, "Erreur via ft_write\n", 21);
    printf("Retour ft_write (stderr) = %zd, errno = %d\n", ret2, errno);

    // Test avec un mauvais fd
    printf("Écriture sur fd invalide :\n");
    errno = 0;
    ssize_t ret3 = ft_write(42, "Invalid FD\n", 11);
    printf("Retour ft_write (fd=42) = %zd, errno = %d\n", ret3, errno);
    perror("Message d'erreur");

    printf("\n");
}


void test_read(void)
{
    printf("=== Test ft_read ===\n");

    // 1) Lecture depuis stdin
    char buffer[100];
    printf("Tape quelque chose (max 99 caractères), puis ENTER :\n");
    ssize_t ret1 = ft_read(0, buffer, 99);
    if (ret1 >= 0)
    {
        buffer[ret1] = '\0';
        printf("ft_read a lu %zd caractères depuis stdin: \"%s\"\n", ret1, buffer);
    }
    else
    {
        perror("Erreur ft_read sur stdin");
    }

    // 2) Lecture d’un fichier
    int fd = open("Makefile", O_RDONLY);
    if (fd == -1)
    {
        perror("Impossible d’ouvrir test.txt");
    }
    else
    {
        ssize_t ret2 = ft_read(fd, buffer, 99);
        if (ret2 >= 0)
        {
            buffer[ret2] = '\0';
            printf("ft_read a lu %zd caractères depuis test.txt: \"%s\"\n", ret2, buffer);
        }
        else
        {
            perror("Erreur ft_read sur test.txt");
        }
        close(fd);
    }

    // 3) Lecture avec un mauvais fd
    errno = 0;
    ssize_t ret3 = ft_read(42, buffer, 10);
    printf("Retour ft_read (fd=42) = %zd, errno = %d\n", ret3, errno);
    perror("Message d'erreur");

    printf("\n");
}


void test_strdup(void)
{
    printf("=== Test ft_strdup ===\n");

    const char *src1 = "Hello 42!";
    char *dup1 = ft_strdup(src1);
    if (dup1)
    {
        printf("Source : \"%s\"\n", src1);
        printf("Dupliqué : \"%s\"\n", dup1);
        printf("Même pointeur ? %s\n", (dup1 == src1) ? "OUI (ERREUR)" : "NON (OK)");
        free(dup1);
    }
    else
        printf("ft_strdup a retourné NULL (ERREUR)\n");

    // Test sur une chaîne vide
    const char *src2 = "";
    char *dup2 = ft_strdup(src2);
    if (dup2)
    {
        printf("Source vide : \"%s\"\n", src2);
        printf("Dupliqué : \"%s\"\n", dup2);
        free(dup2);
    }

    // Test avec une chaîne un peu plus longue
    const char *src3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *dup3 = ft_strdup(src3);
    if (dup3)
    {
        printf("Source longue : \"%s\"\n", src3);
        printf("Dupliqué : \"%s\"\n", dup3);
        free(dup3);
    }

    printf("\n");
}

#include <stdio.h>
#include <string.h>

// Déclaration de ta fonction en ASM

void test_ft_strchr(const char *s, int c)
{
    char *res_ft = ft_strchr(s, c);
    char *res_std = strchr(s, c);

    printf("Test avec s=\"%s\" et c='%c' (ascii %d):\n", s, (c >= 32 && c <= 126) ? c : '?', c);
    printf("   ft_strchr  = %s\n", res_ft ? res_ft : "NULL");
    printf("   strchr     = %s\n", res_std ? res_std : "NULL");
    if (res_ft == res_std || (res_ft && res_std && strcmp(res_ft, res_std) == 0))
        printf("   ✅ Résultat identique\n\n");
    else
        printf("   ❌ Résultat différent\n\n");
}



void test_atoi_base(void)
{
    printf("=== Test ft_atoi_base ===\n");

    // base 10
    printf("ft_atoi_base(\"42\", \"0123456789\") = %d\n", ft_atoi_base("42", "0123456789"));
    printf("ft_atoi_base(\"-123\", \"0123456789\") = %d\n", ft_atoi_base("-123", "0123456789"));

    // base 2 (binaire)
    printf("ft_atoi_base(\"1010\", \"01\") = %d (attendu 10)\n", ft_atoi_base("1010", "01"));
    printf("ft_atoi_base(\"-111\", \"01\") = %d (attendu -7)\n", ft_atoi_base("-111", "01"));

    // base 16 (hexadécimal)
    printf("ft_atoi_base(\"FF\", \"0123456789ABCDEF\") = %d (attendu 255)\n", ft_atoi_base("FF", "0123456789ABCDEF"));
    printf("ft_atoi_base(\"-1A\", \"0123456789ABCDEF\") = %d (attendu -26)\n", ft_atoi_base("-1A", "0123456789ABCDEF"));

    // base 8 (octal)
    printf("ft_atoi_base(\"77\", \"01234567\") = %d (attendu 63)\n", ft_atoi_base("77", "01234567"));

    // erreurs / cas limites
    printf("ft_atoi_base(\"42\", \"0\") = %d (base invalide)\n", ft_atoi_base("42", "0"));
    printf("ft_atoi_base(\"42\", \"012+34\") = %d (base invalide)\n", ft_atoi_base("42", "012+34"));
    printf("ft_atoi_base(\"   1010\", \"01\") = %d (attendu 10, gestion des espaces)\n", ft_atoi_base("   1010", "01"));

    printf("\n");
}



int main(void)
{
    test_strlen();
    test_strcmp();
    test_strcpy();
	test_write();
	test_read();
	test_strdup();

	test_ft_strchr("Hello World", 'W');
    test_ft_strchr("Hello World", 'o');
    test_ft_strchr("Hello World", 'z');    // caractère absent
    test_ft_strchr("Hello World", '\0');   // chercher le null-terminator
    test_ft_strchr("", 'a');               // chaîne vide

	test_atoi_base();
    return 0;
}
