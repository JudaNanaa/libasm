#include <assert.h>
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


typedef struct s_list
{
    void            *data;
    struct s_list   *next;
} t_list;

// déclaration de ta fonction en ASM
void ft_list_push_front(t_list **begin_list, void *data);
int	ft_list_size(t_list *lst);
t_list *ft_create_elem(void *data);
void ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));


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

static t_list *create_node(const char *s)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = strdup(s ? s : "");
    if (!node->data)
    {
        perror("strdup");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->next = NULL;
    return node;
}

/* Helper : affichage de la liste (index + contenu) */
static void print_list(t_list *lst)
{
    int i = 0;
    if (!lst)
    {
        printf("Liste vide\n");
        return;
    }
    while (lst)
    {
        printf("  [%d] %s\n", i, (char *)lst->data);
        lst = lst->next;
        i++;
    }
}

static void free_list(t_list *lst)
{
    t_list *tmp;
    while (lst)
    {
        tmp = lst->next;
        free(lst->data);
        free(lst);
        lst = tmp;
    }
}

void test_ft_list_push_front(void) {
    printf("\n=== Test ft_list_push_front ===\n");

    // Création liste initiale : "B" -> "C" -> NULL
    t_list *list = create_node("B");
    list->next = create_node("C");

    printf("Avant:\n");
    print_list(list);

    // Ajout "A" en tête
    ft_list_push_front(&list, "A");

    printf("Après push_front(\"A\"):\n");
    print_list(list);

    // Vérification simple
    if (list && strcmp(list->data, "A") == 0)
        printf("✅ OK: 'A' est bien en tête\n");
    else
        printf("❌ FAIL: mauvais résultat\n");

    // On peut tester plusieurs pushes successifs
    ft_list_push_front(&list, "Z");
    ft_list_push_front(&list, "Y");

    printf("Après pushes successifs (\"Z\", \"Y\"):\n");
    print_list(list);
}

void test_ft_list_size(void)
{
    printf("=== Test ft_list_size ===\n");

    t_list *list = NULL;

    /* Test 1 : liste vide */
    printf("-- Liste vide --\n");
    assert(ft_list_size(list) == 0);
    printf("OK (size = 0)\n");

    /* Test 2 : liste avec 1 élément */
    list = create_node("One");
    printf("-- Liste avec 1 élément --\n");
    assert(ft_list_size(list) == 1);
    printf("OK (size = 1)\n");

    /* Test 3 : liste avec plusieurs éléments */
    list->next = create_node("Two");
    list->next->next = create_node("Three");
    list->next->next->next = create_node("Four");

    printf("-- Liste avec 4 éléments --\n");
    assert(ft_list_size(list) == 4);
    printf("OK (size = 4)\n");

    /* Nettoyage */
    free_list(list);

    printf("Tous les tests ft_list_size sont passés ✅\n\n");
}


void test_ft_create_elem(void)
{
    printf("=== Test ft_create_elem ===\n");

    /* Test 1 : data simple (string) */
    char *str = strdup("Hello");
    t_list *node = ft_create_elem(str);
    assert(node != NULL);
    assert(node->data == str);   // doit pointer vers la même adresse
    assert(node->next == NULL);
    printf("OK (création avec string)\n");
    free_list(node);

    /* Test 2 : data NULL */
    node = ft_create_elem(NULL);
    assert(node != NULL);
    assert(node->data == NULL);
    assert(node->next == NULL);
    printf("OK (création avec NULL)\n");
    free_list(node);

    /* Test 3 : data numérique */
    int *n = malloc(sizeof(int));
    *n = 42;
    node = ft_create_elem(n);
    assert(node != NULL);
    assert(node->data == n);
    assert(*(int *)node->data == 42);
    assert(node->next == NULL);
    printf("OK (création avec int)\n");
    free_list(node);

    printf("Tous les tests ft_create_elem sont passés ✅\n\n");
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

/* Comparateur pour les int */
int cmp_int(void *a, void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;
    return (ia - ib);
}


static void print_list_str(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}

static void print_list_int(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", *(int *)lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}


void test_ft_list_sort(void)
{
    printf("=== Test ft_list_sort ===\n");

    /* ====== Test 1 : liste de strings ====== */
    t_list *list1 = ft_create_elem(strdup("banana"));
    list1->next = ft_create_elem(strdup("apple"));
    list1->next->next = ft_create_elem(strdup("cherry"));

    printf("Avant tri (strings) : ");
    print_list_str(list1);
    ft_list_sort(&list1, cmp_str);
    printf("Après tri (strings) : ");
    print_list_str(list1);

    assert(strcmp(list1->data, "apple") == 0);
    assert(strcmp(list1->next->data, "banana") == 0);
    assert(strcmp(list1->next->next->data, "cherry") == 0);
    printf("OK (tri string)\n\n");

    /* ====== Test 2 : liste d’int ====== */
    int *a = malloc(sizeof(int)); *a = 42;
    int *b = malloc(sizeof(int)); *b = 7;
    int *c = malloc(sizeof(int)); *c = 19;

    t_list *list2 = ft_create_elem(a);
    list2->next = ft_create_elem(b);
    list2->next->next = ft_create_elem(c);

    printf("Avant tri (int) : ");
    print_list_int(list2);
    ft_list_sort(&list2, cmp_int);
    printf("Après tri (int) : ");
    print_list_int(list2);

    assert(*(int *)list2->data == 7);
    assert(*(int *)list2->next->data == 19);
    assert(*(int *)list2->next->next->data == 42);
    printf("OK (tri int)\n\n");

    /* ====== Test 3 : liste vide ====== */
    t_list *list3 = NULL;
    ft_list_sort(&list3, cmp_str);
    assert(list3 == NULL);
    printf("OK (liste vide)\n\n");

    printf("Tous les tests ft_list_sort sont passés ✅\n\n");
}

// Fonction de free (ici juste printf pour debug)
void free_fct(void *data) {
    printf("freeing: %s\n", (char *)data);
    // pas besoin de free(data) car on a mis des littéraux
}

// ===== Test =====
void test_ft_list_remove_if(void) {
    printf("\n=== Test ft_list_remove_if ===\n");

    // Création liste: "A" -> "B" -> "C" -> "B" -> NULL
    t_list *list = create_node("A");
    list->next = create_node("B");
    list->next->next = create_node("C");
    list->next->next->next = create_node("B");

    printf("Avant suppression:\n");
    print_list(list);

    // Suppression de tous les "B"
    ft_list_remove_if(&list, "B", cmp_str, free_fct);

    printf("Après suppression de \"B\":\n");
    print_list(list);

    // Vérification manuelle
    if (list && strcmp((char *)list->data, "A") == 0 &&
        list->next && strcmp((char *)list->next->data, "C") == 0 &&
        list->next->next == NULL)
    {
        printf("✅ Test OK: tous les 'B' supprimés\n");
    } else {
        printf("❌ Test FAIL\n");
    }
}

// Test suppression en tête
void test_remove_head(void) {
    printf("\n=== Test suppression en tête ===\n");
    t_list *list = create_node("X");
    list->next = create_node("Y");
    list->next->next = create_node("Z");

    printf("Avant:\n");
    print_list(list);

    ft_list_remove_if(&list, "X", cmp_str, free_fct);

    printf("Après suppression de \"X\":\n");
    print_list(list);
}

// Test suppression en queue
void test_remove_tail(void) {
    printf("\n=== Test suppression en queue ===\n");
    t_list *list = create_node("X");
    list->next = create_node("Y");
    list->next->next = create_node("Z");

    printf("Avant:\n");
    print_list(list);

    ft_list_remove_if(&list, "Z", cmp_str, free_fct);

    printf("Après suppression de \"Z\":\n");
    print_list(list);
}

// Test suppression du seul élément
void test_remove_single(void) {
    printf("\n=== Test suppression du seul élément ===\n");
    t_list *list = create_node("ONE");

    printf("Avant:\n");
    print_list(list);

    ft_list_remove_if(&list, "ONE", cmp_str, free_fct);

    printf("Après suppression de \"ONE\":\n");
    print_list(list);
}

// Test suppression inexistante (ne doit rien changer)
void test_remove_not_found(void) {
    printf("\n=== Test suppression inexistante ===\n");
    t_list *list = create_node("A");
    list->next = create_node("B");

    printf("Avant:\n");
    print_list(list);

    ft_list_remove_if(&list, "Z", cmp_str, free_fct);

    printf("Après suppression de \"Z\":\n");
    print_list(list);
}

// Test liste vide
void test_remove_empty(void) {
    printf("\n=== Test liste vide ===\n");
    t_list *list = NULL;

    ft_list_remove_if(&list, "X", cmp_str, free_fct);

    printf("Après suppression sur liste vide:\n");
    print_list(list);
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

	test_ft_create_elem();

	test_ft_list_push_front();
	test_ft_list_size();
	test_ft_list_sort();

    // test_ft_list_remove_if();   // suppression au milieu avec doublons
    test_remove_head();         // suppression du premier élément
    test_remove_tail();         // suppression du dernier
    test_remove_single();       // suppression unique node
    test_remove_not_found();    // data_ref non présente
    test_remove_empty();        // liste vide
    return 0;
}
