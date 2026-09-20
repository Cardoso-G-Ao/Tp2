import java.util.Scanner;

public class MainEx1 {
    public  static void main(String[] args){
        Veiculo[] veiculosVetor = LeitorCsv.Ler("veiculos.csv");
        Scanner sc = new Scanner(System.in);
        int id = sc.nextInt();
        while (id != -1) {
        for(int i = 0; i < veiculosVetor.length ; i++){
            if(veiculosVetor[i].getId() == id){
                System.out.println(veiculosVetor[i].format());
            }
        }
        }
    }
}
