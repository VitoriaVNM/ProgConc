class Lab3 implements Runnable{

     private final int size;
     private final int id;   
     private double valor = 0;

    public Lab3(int N, int i) {
        this.size = N;
        this.id = i;
    }

    /*método executado pelas threads*/
    public void run(){
        int t = 3000; //nmr de termos
        for(int j = 0; j <= t; j++){
            if(j % size == id){
                valor += Math.pow(-1, j) / (2 * j + 1);
            }
        }
    }


    public double getValor(){
        return valor;
    }
}

class Main {
    static final int N = 2; //qtd de threads
    static double valor = 0;

    public static void main(String[] args) {

        Thread[] threads = new Thread[N]; //vetor de threads
        Lab3[] labs = new Lab3[N]; //vetor de objetos Lab3

        //objeto runnable em thread
        for(int i = 0; i < threads.length; i++ ){
            labs[i] = new Lab3(N, i); //cria instância de Lab3
            threads[i] = new Thread(labs[i]);
        }

        //inicia as threads
        for(int j = 0; j < threads.length; j++){
            threads[j].start();
        }


        //espera pelo fim das threads
        for(int f = 0; f < threads.length; f++){
            try{threads[f].join();}
            catch (InterruptedException e) {return;}
        }

        for(int k = 0; k < threads.length; k++){
            valor += labs[k].getValor();
        }

        //verificando o valor com base na diferença com pi
        double pi = 4*valor;
        double dif = (pi - Math.PI);

        System.out.println(" Diferença entre pi e o valor encontrado: "+ dif);

    }
   

}