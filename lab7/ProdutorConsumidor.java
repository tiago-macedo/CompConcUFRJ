//=============================================================//
//  Lab 7 - Computação Concorrente - UFRJ                      //
//  Tiago Macedo - DRE 116022689                               //
//  ---------------------------------------------------------  //
//  Para usar o programa:                                      //
//    java ProdutorConsumidor [TAM VETOR] [PRODS] [CONSUMS]    //
//  onde:                                                      //
//    [TAM VEC] é o tamanho do vetor                           //
//    [PRODS] é a quantidade de threads produtoras             //
//    [CONSUMS] é a quantidade de threads consumidoras         //
//=============================================================//

import java.util.ArrayList;
import java.util.Random;

// Classe utilitária para gerar valores para o programa
//-----------------------------------------------------

class Ajudante {
//	private static Ajudante single = new Ajudante();
	private static final int MAX = 99;			// maior inteiro produzível por thread produtora
	private static final double T_MEDIO = 2.0;	// tempo médio de espera (segundos)
	private static final double D_PADRAO = 1.0;	// desvio padrão do tempo de espera (segundos)
	private static final Random ran = new Random();
	

	// Método usado por threads produtoras para
	// gerar inteiros alieatórios
	//-----------------------------------------
	public static int produzir() {
		return ran.nextInt(MAX);
	}
	
	
	// Método usado para esperar uma quantidade
	// de tempo aleatória, mas que não varie
	// drásticamente
	//-----------------------------------------
	
	public static void esperar() {
		long t = (long) ( 1000.0 * (D_PADRAO * ran.nextGaussian() + T_MEDIO) );	// tempo a esperar (aleatório)
		if (t < 0L) t = 0L;	// sem tempo negativo
		try { Thread.sleep(t); }
		catch (InterruptedException e) { e.printStackTrace(); }
	}
}


// Classe do buffer thread-safe
//-----------------------------

class SyncBuffer {

	// Variáveis
	//--------------------
	
	private Integer cap;			// capacidade do buffer
	private Integer num;			// quantidade atual de itens
	private ArrayList<Integer> buf;	// buffer
	
	
	// Construtor
	//--------------------
	
	SyncBuffer(Integer _cap) {
		this.cap = _cap;
		this.num = 0;
		this.buf = new ArrayList<Integer>(this.cap);
	}
	
	
	// Métodos
	//--------------------
	
	public synchronized Integer pop() {
		while (this.num == 0) {	// se buffer vazio...	
			try {
				System.out.println("Buffer vazio!\nBotando thread em espera.");
				wait();			// ...pause leitura
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		notifyAll();
		System.out.print("[MNT]: pop() = ");
		this.num--;
		Integer elem = this.buf.get(this.num);
		this.buf.remove(this.num);
		System.out.printf("%d: retirado da posição %d.\n", elem, this.num);
		return elem;
	}
	
	public synchronized void push(Integer elem) {
		while (this.num == cap)	{	// se buffer cheio...
			try {
				System.out.println("Buffer cheio!\nBotando thread em espera.");
				wait();				// ...pause escrita
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		notifyAll();
		System.out.printf("[MNT]: push(%d): ", elem);
		this.buf.add(this.num, elem);
		System.out.printf("adicionado em posição %d.\n", this.num);
		this.num++;
	}
	
	public synchronized String toString() {
		StringBuilder sb = new StringBuilder("[ ");
		for (int i=0; i<this.num; i++) {
			sb.append(this.buf.get(i));
			sb.append(" ");
		}
		sb.append("]");
		return sb.toString();
	}
}


// Classe de thread produtora
//---------------------------

class Produtor extends Thread {
	int id;
	SyncBuffer syb;
	
	Produtor(int _id, SyncBuffer _syb) {
		this.id = _id;
		this.syb = _syb;
		System.out.printf("Thread produtora %d criada!\n", this.id);
	}
	
	public void run() {
		int x;
		while (true) {
			x = Ajudante.produzir();
			System.out.printf("[P%d]: push(%d)\n", this.id, x);
			syb.push(x);
			Ajudante.esperar();
		}
	}
}


// Classe de thread consumidora
//-----------------------------

class Consumidor extends Thread {
	int id;
	SyncBuffer syb;
	
	Consumidor (int _id, SyncBuffer _syb) {
		this.id = _id;
		this.syb = _syb;
		System.out.printf("Thread consumidora %d criada!\n", this.id);
	}
	
	public void run() {
		int x;
		while (true) {
			System.out.printf("[C%d]: pop()\n", this.id);
			x = syb.pop();
			System.out.printf("[C%d]: pop retornou %d\n", this.id, x);
			Ajudante.esperar();
		}
	}
}


// Classe principal
//-----------------

public class ProdutorConsumidor {
	public static void main(String[] args) {
		// Inicializando buffer com tamanho dado pela
		// linha de comando
		SyncBuffer b = new SyncBuffer( args.length == 0 ? 5 : Integer.parseInt(args[0]) );
		
		// Criando threads em quantidade dada pela
		// linha de comando
		int numProds = args.length < 2 ? 1 : Integer.parseInt(args[1]);
		int numConsums = args.length < 2 ? 1 : Integer.parseInt(args[2]);
		Produtor[] produtores = new Produtor[numProds];
		Consumidor[] consumidores = new Consumidor[numConsums];
		for (int i = 0; i < numProds; i++)
			produtores[i] = new Produtor(i, b);
		for (int i = 0; i < numConsums; i++)
			consumidores[i] = new Consumidor(i, b);
		
		// Inicializando threads
		for (int i = 0; i < numProds; i++)
			produtores[i].start();
		for (int i = 0; i < numConsums; i++)
			consumidores[i].start();

		// Main será responsável por, periodicamente,
		// imprimir vetor inteiro.
		while(true) {
			System.out.println("[MAIN]: " + b.toString());
			Ajudante.esperar();
		}
	}
}
