
public class Tester {

	public Tester()
	{
		
	}
	
	public static void main(String[] args) {
		int x = 0;
		System.out.print(((0xFF << (3 << 3)) | (0xFE << (2 << 3)) | (0x32 <<(1 << 3)) | 0xFF) & ~0x00000000);
		x = x| (0xFE << (3 << 3));
		System.out.print(x);
	}
}
