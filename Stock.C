#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define NOM_TAILLE 50

typedef struct {
    char id[20];
    char nom[NOM_TAILLE];
    int quantite;
} Produit;

Produit stock[MAX];
int totalProduits = 0;

void chargerProduits() {
    FILE *fichier = fopen("stock.txt", "r");
    if (fichier == NULL) return;

    while (fscanf(fichier, "%s %s %d", stock[totalProduits].id, stock[totalProduits].nom, &stock[totalProduits].quantite) != EOF) {
        totalProduits++;
    }

    fclose(fichier);
}

void sauvegarderProduits() {
    FILE *fichier = fopen("stock.txt", "w");
    for (int i = 0; i < totalProduits; i++) {
        fprintf(fichier, "%s %s %d\n", stock[i].id, stock[i].nom, stock[i].quantite);
    }
    fclose(fichier);
}

void ajouterProduit() {
    if (totalProduits >= MAX) {
        printf("Stock plein !\n");
        return;
    }

    printf("ID du produit : ");
    scanf("%s", stock[totalProduits].id);
    printf("Nom du produit : ");
    scanf("%s", stock[totalProduits].nom);
    printf("Quantité : ");
    scanf("%d", &stock[totalProduits].quantite);
    totalProduits++;

    printf("Produit ajouté avec succès.\n");
}

void modifierProduit() {
    char id[20];
    printf("Entrez l'ID du produit à modifier : ");
    scanf("%s", id);

    for (int i = 0; i < totalProduits; i++) {
        if (strcmp(stock[i].id, id) == 0) {
            printf("Nouveau nom : ");
            scanf("%s", stock[i].nom);
            printf("Nouvelle quantité : ");
            scanf("%d", &stock[i].quantite);
            printf("Produit modifié.\n");
            return;
        }
    }

    printf("Produit non trouvé.\n");
}

void supprimerProduit() {
    char id[20];
    printf("Entrez l'ID du produit à supprimer : ");
    scanf("%s", id);

    for (int i = 0; i < totalProduits; i++) {
        if (strcmp(stock[i].id, id) == 0) {
            for (int j = i; j < totalProduits - 1; j++) {
                stock[j] = stock[j + 1];
            }
            totalProduits--;
            printf("Produit supprimé.\n");
            return;
        }
    }

    printf("Produit non trouvé.\n");
}

void afficherProduits() {
    if (totalProduits == 0) {
        printf("Aucun produit dans le stock.\n");
        return;
    }

    printf("\nListe des produits :\n");
    for (int i = 0; i < totalProduits; i++) {
        printf("ID: %s | Nom: %s | Quantité: %d\n", stock[i].id, stock[i].nom, stock[i].quantite);
    }
}

void rechercherProduit() {
    char recherche[50];
    printf("Entrer le nom ou l'ID du produit : ");
    scanf("%s", recherche);

    for (int i = 0; i < totalProduits; i++) {
        if (strcmp(stock[i].id, recherche) == 0 || strcmp(stock[i].nom, recherche) == 0) {
            printf("Produit trouvé : ID: %s | Nom: %s | Quantité: %d\n", stock[i].id, stock[i].nom, stock[i].quantite);
            return;
        }
    }

    printf("Aucun produit trouvé.\n");
}

void menu() {
    int choix;

    do {
        printf("\n=== MENU GESTION DE STOCK ===\n");
        printf("1. Ajouter un produit\n");
        printf("2. Modifier un produit\n");
        printf("3. Supprimer un produit\n");
        printf("4. Afficher tous les produits\n");
        printf("5. Rechercher un produit\n");
        printf("6. Sauvegarder et quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterProduit(); break;
            case 2: modifierProduit(); break;
            case 3: supprimerProduit(); break;
            case 4: afficherProduits(); break;
            case 5: rechercherProduit(); break;
            case 6: sauvegarderProduits(); printf("Sauvegarde effectuée. Au revoir.\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 6);
}

int main() {
    chargerProduits();
    menu();
    return 0;
}