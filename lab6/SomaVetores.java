class ThreadStruct {
	public int id;
	public int num;
	public ThreadStruct(int _id, int _num) {
		this.id = _id;
		this.num = _num;
	}
}

class Vetor {
	private int dim;
	private int[] elementos;
	
	public Vetor(int _dim) { 
		this.dim = _dim;
		this.elementos = new int[this.dim];
	}
	
	// Escrita:
	public synchronized void set(int index, int valor) { 
		this.elementos[index] = valor;
	}
	// Leitura:
	public synchronized int get(int index) { 
		return this.elementos[index];
	}
	public synchronized int dim() {
		return this.dim;
	}
	public void print() {
		System.out.print("[ ");
		for (int i=0; i<this.dim; i++) {
			System.out.print(this.get(i));
			System.out.print(" ");
		}
		System.out.println("]");
	}
	
}

class Th extends Thread {
	private ThreadStruct info;
	Vetor a, b, c;
	
	public Th(ThreadStruct _info, Vetor _a, Vetor _b, Vetor _c) { 
		this.info = _info;
		this.a = _a;
		this.b = _b;
		this.c = _c;
	}
	
	public void run() {
		for (	int i=this.info.id;
				i<this.c.dim();
				i+=this.info.num)
		{
			System.out.printf("Thread %d somando elemento %d\n", this.info.id, i);
			this.c.set(i, this.a.get(i) + this.b.get(i));
		}
	}
}

class SomaVetores {
	static int NThreads;
	static int NElementos;
	
	public static void main (String[] args) {
		// Verificando entrada de parâmetros:
		if (args.length < 2) {
			System.out.println("Uso:");
			System.out.println("	java SomaVetores <dimensão dos vetores> <número de threads>");
			return;
		}
		
		// Usuário determina número de threads:
		NThreads = Integer.parseInt(args[1]);
		Thread[] threads = new Thread[NThreads];
		ThreadStruct[] infos = new ThreadStruct[NThreads];
		
		// Inicialização dos arrays:
		NElementos = Integer.parseInt(args[0]);
		Vetor a = new Vetor(NElementos);
		Vetor b = new Vetor(NElementos);
		Vetor c = new Vetor(NElementos);
		for (int i=0; i<NElementos; i++) {
			a.set(i, i);
			b.set(i, NElementos-i);
		}
		System.out.print("a = ");
		a.print();
		System.out.print("b = ");
		b.print();

		// Cria as threads da aplicação:
		for (int i=0; i<NThreads; i++) {
			infos[i] = new ThreadStruct(i, NThreads);
			threads[i] = new Th(infos[i], a, b, c);
		}

		// É dada a largada:
		for (int i=0; i<NThreads; i++) {
			 threads[i].start();
		}

		// Espera o término:
		for (int i=0; i<NThreads; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				return;
			}
		}
		
		// Imprime o resultado:
		System.out.print("c = ");
		c.print();
	}
}
