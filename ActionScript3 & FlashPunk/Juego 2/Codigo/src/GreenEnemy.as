package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	
	public class GreenEnemy extends Entity
	{
		[Embed(source = "../assets/spaceship1.png")] private const GREENENEMY_IMG:Class;
		
		private var greenEnemyImg:Image;
		private var dir:int = 1;
		private var vel:uint = 0;
		
		public function GreenEnemy(px:uint = 0, py:uint = 0)
		{
			greenEnemyImg = new Image(GREENENEMY_IMG);
			greenEnemyImg.color = 0x00DD00;
			graphic = greenEnemyImg;
			x = px;
			y = py;
			if (y == 0)
				dir = 1;
			else
				dir = -1;
			vel = 200;
			mask = new Pixelmask(GREENENEMY_IMG);
			type = "GreenEnemy";			
		}
		
		override public function update():void
		{				
			if (dir == 1)
			{
				if ((y + greenEnemyImg.height) < FP.screen.height)
					y += FP.elapsed * vel;
				else
					world.remove(this);
			}
			
			if (dir == -1)
			{
				if (y > 0)
					y -= FP.elapsed * vel;
				else
					world.remove(this);
			}
			
			if (collide("Player", x, y))
			{
				world.remove(this);
				
				if (Player.estado == 2)
					GameWorld.gameScore.addScore();
				else
					GameWorld.gameScore.removeScore();
			}
		}		
	}
}