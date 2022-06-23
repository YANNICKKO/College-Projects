int n, m, constanta = 1, **matrice, col = 0, lin = 0;
    int alocare_check = 0, dim_max = 1, dim_actuala = 0;
    int maxim_a, directie_a;
    int palindrom_b = 2, prim_b, este_prim = 1;
    int dimensiune_c, saritura_c, suma_c = 0;
    scanf("%d %d\n", &n, &m);
    char *cod, *juma_de_cod, *temp;

    // alocare dinamica
    cod = (char *)calloc(dim_max, sizeof(char));

    if (cod == NULL) {
        printf("Unde e memoria boss???");
        return;
    }

    while (alocare_check == 0) {
        if (dim_actuala > dim_max) {
            dim_max *= 2;
            temp = realloc(cod, dim_max);
            if (temp == NULL) {
                printf("Unde e memoria, boss???");
                break;
            } else {
                cod = temp;
            }
        }

        scanf("%c", &cod[dim_actuala]);
        if (!((cod[dim_actuala] >= 'a' && cod[dim_actuala] <= 'c') || (cod[dim_actuala] >= '0' && cod[dim_actuala] <= '9') || (cod[dim_actuala] == ' '))) {
        // if(cod[dim_actuala] == '\n')
            cod[dim_actuala] = '\0';
            alocare_check = 1;
        }

        dim_actuala++;
    }

    matrice = (int **)calloc(n, sizeof(int *));

    if (matrice == NULL) {
        printf("Unde e memoria boss???");
        return;
    }

    for (int i = 0; i < n; i++) {
        matrice[i] = (int *)calloc(m, sizeof(int));
        if (matrice[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(matrice[j]);
            free(matrice);
            printf("Unde e memoria boss???");
            return;
        }
    }

    //=======================

    juma_de_cod = strtok(cod, " ");

    matrice[lin][col] = constanta;
    constanta++;

    while (juma_de_cod != NULL) {
        if (juma_de_cod[0] == 'a') {
            directie_a = 1;
            maxim_a = juma_de_cod[1];
            for (int i = 0; i < 3; i++) {
                if (juma_de_cod[i + 2] > maxim_a) {
                    directie_a = i + 2;
                    maxim_a = juma_de_cod[i + 2];
                }
            }
            switch (directie_a) {
            case 1:
                col++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 2:
                lin--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 3:
                col--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 4:
                lin++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            }
        }

        //--------------------------

        if (juma_de_cod[0] == 'b') {
            // algoritm prim
            prim_b = juma_de_cod[strlen(juma_de_cod) - 1] - '0';
            prim_b += (juma_de_cod[strlen(juma_de_cod) - 2] - '0') * 10;
            for (int i = 2; i < prim_b / 2 && este_prim == 1; i++) {
                if (prim_b % i == 0)
                    este_prim = 0;
            }

            // algoritm palindrom
            for (long unsigned int i = 0; i < (strlen(juma_de_cod) - 1) / 2 && palindrom_b == 2; i++) {
                if (juma_de_cod[1 + i] != juma_de_cod[strlen(juma_de_cod) - 1 - i]) {
                    palindrom_b = 0;
                }
            }

            // cand e palindrom +2, cand e prim +1
            switch (este_prim + palindrom_b) {
            case 2:
                col++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 1:
                lin--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 3:
                col--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 0:
                lin++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            }
            este_prim = 1;
            palindrom_b = 2;
        }

        //--------------------------

        if (juma_de_cod[0] == 'c') {
            dimensiune_c = juma_de_cod[1] - '0';
            saritura_c = juma_de_cod[2] - '0';
            for (int i = 0; i < saritura_c; i++) {
                suma_c += juma_de_cod[((i * saritura_c) % dimensiune_c) + 3] - '0';
            }
            switch (suma_c % 4) {
            case 2:
                col++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 1:
                lin--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 0:
                col--;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            case 3:
                lin++;
                matrice[lin][col] = constanta;
                constanta++;
                break;
            }
            suma_c = 0;
        }
        juma_de_cod = strtok(NULL, " ");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }

    // dezalocare chestii
    for (int i = 0; i < n; i++)
        free(matrice[i]);
    free(matrice);
    free(cod);