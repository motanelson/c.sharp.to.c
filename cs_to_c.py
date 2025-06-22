import re

def converter_csharp_para_c(codigo_cs):
    linhas = codigo_cs.splitlines()
    saida = []
    leu_arquivo = False

    for linha in linhas:
        linha = linha.strip()

        # using => include
        if linha.startswith("using "):
            nome = linha.replace("using", "").replace(";", "").strip()
            saida.append(f'#include "{nome}.h"')
            continue

        # Ignorar namespace/classe/chaves
        if linha.startswith("namespace ") or linha.startswith("class "):
            continue
        if linha in ("{", "}"):
            continue

        # Substituições básicas
        linha = linha.replace("string", "char*")
        linha = re.sub(r'\b(public|private|static|internal|protected|virtual|override)\b', '', linha)
        linha = re.sub(r'\s+', ' ', linha).strip()

        # Conversão de File.ReadAllText
        if "File.ReadAllText" in linha:
            leu_arquivo = True
            saida.append('FILE* ficheiro = fopen("out.txt", "r");')
            saida.append('if (ficheiro == NULL) {')
            saida.append('    printf("Erro ao abrir o ficheiro.\\n");')
            saida.append('    return;')
            saida.append('}')
            saida.append('char linha[1024];')
            saida.append('while (fgets(linha, sizeof(linha), ficheiro)) {')
            continue

        # Impressão com printf
        if "Console.WriteLine" in linha:
            if leu_arquivo:
                saida.append('    printf("%s", linha);')
                saida.append('}')
                saida.append('fclose(ficheiro);')
                leu_arquivo = False
            else:
                conteudo = re.findall(r'Console\.WriteLine\((.*)\);', linha)
                if conteudo:
                    saida.append(f'printf({conteudo[0]});')
            continue

        # Adicionar cabeçalho da função
        if linha.startswith("void Main()"):
            saida.append("void Main() {")
            continue

        if linha and not leu_arquivo:
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
