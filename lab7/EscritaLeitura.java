import java.util.ArrayList;
//import java.lang.Object;

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
			try { wait(); }		// ...pause leitura
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.num--;
		Integer elem = this.buf.get(this.num);
		this.buf.remove(this.num);
		return elem;
	}
	
	public synchronized void push(Integer elem) {
		while (this.num == cap)	{	// se buffer cheio...
			try { wait(); }			// ...pause escrita
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.buf.add(this.num, elem);
		this.num++;
	}
}

public class EscritaLeitura {
	public static void main(String[] args) {
		SyncBuffer b = new SyncBuffer(5);
		b.push(4);
		Integer c = b.pop();
		b.push(9);
		System.out.println(c);
	}
}
