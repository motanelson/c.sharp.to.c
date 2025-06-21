
import re

def converter_csharp_para_c(codigo_cs):
    linhas = codigo_cs.splitlines()
    saida = []

    for linha in linhas:
        linha = linha.strip()

        # Converte using para include
        if linha.startswith("using "):
            nome = linha.replace("using", "").replace(";", "").strip()
            saida.append(f'#include "{nome}.h"')
            continue

        # Remove namespace e class
        if linha.startswith("namespace ") or linha.startswith("class "):
            continue
        if linha == "{" or linha == "}":
            continue

        # Substituição simples de tipos
        linha = linha.replace("string", "char*")
        linha = linha.replace("int", "int")
        linha = linha.replace("void", "void")

        # Remove modificadores C#
        linha = re.sub(r'\b(public|private|static|internal|protected|virtual|override)\b', '', linha)
        linha = re.sub(r'\s+', ' ', linha).strip()

        # Substituir Console.WriteLine por printf
        linha = linha.replace("Console.WriteLine", "printf")
        linha = re.sub(r'printf\((.*?)\);', r'printf(\1);', linha)

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
