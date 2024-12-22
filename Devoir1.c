#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Fonction f(n) = 2^n
int f(int n) {
    return pow(2, n);
}

// Fonction g(n) = 2*n
int g(int n) {
    return 2 * n;
}

int main(int argc, char *argv[]) {
    int opt;
    int has_f = 0, has_g = 0;
    int n = 0;
    int result;
    char first_opt = '\0';
    
    // Vérifier qu'il y a au moins une option
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-f n] [-g n]\n", argv[0]);
        exit(1);
    }

    // On désactive le message d'erreur par défaut de getopt
    opterr = 0;

    // Parcourir les options
    while ((opt = getopt(argc, argv, "f::g::")) != -1) {
        switch (opt) {
            case 'f':
                has_f = 1;
                if (first_opt == '\0') {
                    first_opt = 'f';
                    if (optarg == NULL && optind < argc && argv[optind] != NULL 
                        && argv[optind][0] != '-') {
                        n = atoi(argv[optind]);
                        optind++;
                    } else if (optarg != NULL) {
                        n = atoi(optarg);
                    } else {
                        fprintf(stderr, "L'option -f nécessite un argument quand elle est première\n");
                        exit(1);
                    }
                }
                break;
            case 'g':
                has_g = 1;
                if (first_opt == '\0') {
                    first_opt = 'g';
                    if (optarg == NULL && optind < argc && argv[optind] != NULL 
                        && argv[optind][0] != '-') {
                        n = atoi(argv[optind]);
                        optind++;
                    } else if (optarg != NULL) {
                        n = atoi(optarg);
                    } else {
                        fprintf(stderr, "L'option -g nécessite un argument quand elle est première\n");
                        exit(1);
                    }
                }
                break;
            case '?':
                if (optopt == 'f' || optopt == 'g') {
                    // C'est normal si c'est la deuxième option
                    if (first_opt != '\0') continue;
                    fprintf(stderr, "L'option -%c nécessite un argument quand elle est première\n", 
                            optopt);
                } else {
                    fprintf(stderr, "Option inconnue: -%c\n", optopt);
                }
                exit(1);
            default:
                abort();
        }
    }

    // Calculer le résultat en fonction des options
    if (has_f && !has_g) {
        // Seulement f
        result = f(n);
        printf("f(%d) = %d\n", n, result);
    }
    else if (!has_f && has_g) {
        // Seulement g
        result = g(n);
        printf("g(%d) = %d\n", n, result);
    }
    else if (has_f && has_g) {
        // Composition de fonctions
        if (first_opt == 'f') {
            result = f(g(n));
            printf("f(g(%d)) = %d\n", n, result);
        } else {
            result = g(f(n));
            printf("g(f(%d)) = %d\n", n, result);
        }
    }

    return 0;
}