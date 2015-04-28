package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	public class Cuadro2 extends Entity
	{
		[Embed(source = "Cuadro2.png")]
		private const CUADRO2_IMG:Class;
		private var cuadro2Img:Image;
		
		public function Cuadro2(px:Number = 0, py:Number = 0)		
		{
			this.cuadro2Img = new Image(CUADRO2_IMG);
			this.graphic = cuadro2Img;
			this.x = px * 16;
			this.y = py * 16;
			setHitbox(cuadro2Img.width, cuadro2Img.height);
			type = "Cuadro2";
		}
		
		override public function update():void
		{
			if (this.collide("Cuadro1", this.x, this.y))
			{
				world.remove(this);
			}
			
			super.update();
		}
		
	}

}