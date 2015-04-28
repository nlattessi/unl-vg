package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	public class Wall extends Entity
	{
		[Embed(source = "Wall.png")]
		private const WALL_IMG:Class;
		private var wallImg:Image;
		
		public function Wall(px:Number = 0, py:Number = 0) 
		{
			this.wallImg = new Image(WALL_IMG);
			this.graphic = wallImg;
			this.x = px * 32;
			this.y = py * 32;
			setHitbox(wallImg.width, wallImg.height);
			type = "Wall";
		}
		
		public override function update():void
		{
			if (collide("Portal", x, y))
			{
				world.remove(this);
			}
			
			super.update();
		}
	}

}