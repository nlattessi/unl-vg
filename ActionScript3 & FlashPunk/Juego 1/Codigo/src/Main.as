package 
{
	import net.flashpunk.Engine;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	[SWF(width = "640", height = "480")]
	
	
	public class Main extends Engine 
	{
		
		public function Main():void 
		{
			super(640, 480, 30, false);
						
			FP.world = new GameWorld();
		}		
	}
	
}