import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

// LeitorCsv l = new LeitorCsv();
// l.ler("/tmp/veiculos.csv");
// l.ler("/documentos/veiculos.csv");
public class LeitorCsv {
    public static Veiculo[] Ler(String caminhoArquivo) {
        File f = new File(caminhoArquivo);
        Veiculo[] vetorVeiculos = new Veiculo[501];
        try {
            Scanner sc = new Scanner(f);
            String cabecalho = sc.nextLine();
            for (int j = 0; j < 500; j++) {
                String ler = sc.nextLine();
                Veiculo veiculo = Veiculo.parseVeiculo(ler);
                vetorVeiculos[j] = veiculo;
            }
        
        } catch (FileNotFoundException e) {
            System.out.println(e);
        }
        return vetorVeiculos;
    }
}