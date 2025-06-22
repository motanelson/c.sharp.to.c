using System;
using System.IO;

class Programa {
    public static void Main() {
        string conteudo = File.ReadAllText("out.txt");
        Console.WriteLine(conteudo);
        File.WriteAllText("out.dat", conteudo);
    }
}
