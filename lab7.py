from threading import Thread
from threading import Lock
import math as m
import time

#classe variavel compartilhada
class Variavel():
    def __init__(self):
        self.valor = 0
        self.lock = Lock()

    def calcula_pi(self, size,id):
        
        n = 3000; #nmr de termos
        self.lock.acquire()
        for j in range(n+1):
            if(j % size == id):
                self.valor += m.pow(-1, j) / (2 * j + 1)     
        self.lock.release()

    def getValor(self):
        return self.valor

#classe da thread
class IncrementaThread(Thread):
    def __init__(self, id, variavel, size):
        super().__init__()
        self.threadid = id
        self.variavel = variavel
        self.size = size

    def run(self):
        self.variavel.calcula_pi(self.size,self.threadid)

#fluxo principal
if __name__ == '__main__':
    #cria variavel compartilhada
    var = Variavel()
    N = 4
    #cria e dispara as threads
    threads = [IncrementaThread(i, var, N) for i in range(N)]

    tempo_inicial = time.time()
    for thread in threads:
        thread.start()
    #aguarda as threads terminarem
    for thread in threads:
        thread.join()
    tempo_final = time.time()
    #exibe o valor da variavel
    print("variavel = ", 4*var.getValor(),"\n")
    print("Erro absoluto:", abs(m.pi-4*var.getValor()), "\n")
    print("Tempo de execução com ", N, "threads:", (tempo_final - tempo_inicial))    