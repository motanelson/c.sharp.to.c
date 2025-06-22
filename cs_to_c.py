import re

def converter_csharp_para_c(codigo_cs):
    linhas = codigo_cs.splitlines()
    saida = []

    for linha in linhas:
        linha = linha.strip()

        # using => include
        if linha.startswith("using "):
            nome = linha.replace("using", "").replace(";", "").strip()
            saida.append(f'#include "{nome}.h"')
            continue

        # Ignorar namespace, class, chaves
        if linha.startswith("namespace ") or linha.startswith("class "):
            continue
        if linha in ("{", "}"):
            continue

        # Substituição de ponto em chamadas de função
        linha = re.sub(r'(\w+)\.(\w+)', r'\1_\2', linha)

        # Modificadores desnecessários
        linha = re.sub(r'\b(public|private|static|internal|protected|virtual|override)\b', '', linha)
        linha = re.sub(r'\s+', ' ', linha).strip()

        if linha.startswith("string"):
            linha = linha.replace("string", "char*")

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
