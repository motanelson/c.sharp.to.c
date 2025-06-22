import re

def converter_csharp_para_c(codigo_cs):
    linhas = codigo_cs.splitlines()
    saida = []
    faz_leitura = False
    faz_escrita = False

    for linha in linhas:
        linha = linha.strip()

        # using => include
        if linha.startswith("using "):
            nome = linha.replace("using", "").replace(";", "").strip()
            saida.append(f'#include "{nome}.h"')
            continue

        # Ignorar namespace, class, chaves isoladas
        if linha.startswith("namespace ") or linha.startswith("class "):
            continue
        if linha in ("{", "}"):
            continue

        # Substituições de tipos
        linha = linha.replace("string", "char*")
        linha = re.sub(r'\b(public|private|static|internal|protected|virtual|override)\b', '', linha)
        linha = re.sub(r'\s+', ' ', linha).strip()

        # Leitura do ficheiro
        if "File.ReadAllText" in linha:
            faz_leitura = True
            saida.append('FILE* ficheiro = fopen("out.txt", "r");')
            saida.append('if (ficheiro == NULL) {')
            saida.append('    printf("Erro ao abrir o ficheiro.\\n");')
            saida.append('    return;')
            saida.append('}')
            saida.append('char linha[1024];')
            continue

        # Escrita do ficheiro
        if "File.WriteAllText" in linha:
            faz_escrita = True
            saida.append('FILE* destino = fopen("out.dat", "w");')
            saida.append('if (destino == NULL) {')
            saida.append('    printf("Erro ao criar o ficheiro de saída.\\n");')
            saida.append('    fclose(ficheiro);')
            saida.append('    return;')
            saida.append('}')
            continue

        # Console.WriteLine => printf e fputs
        if "Console.WriteLine" in linha:
            if faz_leitura and faz_escrita:
                saida.append('while (fgets(linha, sizeof(linha), ficheiro)) {')
                saida.append('    printf("%s", linha);')
                saida.append('    fputs(linha, destino);')
                saida.append('}')
                saida.append('fclose(ficheiro);')
                saida.append('fclose(destino);')
                faz_leitura = False
                faz_escrita = False
            elif faz_leitura:
                saida.append('while (fgets(linha, sizeof(linha), ficheiro)) {')
                saida.append('    printf("%s", linha);')
                saida.append('}')
                saida.append('fclose(ficheiro);')
                faz_leitura = False
            continue

        if linha.startswith("void Main()"):
            saida.append("void Main() {")
            continue

        if linha:
            saida.append(linha)

    return "\n".join(saida)


def main():
    ficheiro_entrada = input("Nome do ficheiro C# (.cs): ").strip()
    ficheiro_saida = ficheiro_entrada.replace(".cs", ".c")

    try:
        with open(ficheiro_entrada, 'r', encoding='utf-8') as f:
            codigo_cs = f.read()

        codigo_c = converter_csharp_para_c(codigo_cs)

        with open(ficheiro_saida, 'w', encoding='utf-8') as f:
            f.write(codigo_c)

        print(f"Conversão concluída! Criado: {ficheiro_saida}")

    except FileNotFoundError:
        print("Ficheiro não encontrado.")



print("\033c\033[43;30m\n")
if __name__ == "__main__":
    main()
