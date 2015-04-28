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
	
	public class RedEnemy extends Entity
	{
		[Embed(source = "../assets/spaceship1.png")] private const REDENEMY_IMG:Class;
		
		private var redEnemyImg:Image;
		private var dir:int = 1;
		private var vel:uint = 0;
		
		public function RedEnemy(px:uint = 0, py:uint = 0)
		{
			redEnemyImg = new Image(REDENEMY_IMG);
			redEnemyImg.color = 0xDD0000;
			graphic = redEnemyImg;
			x = px;
			y = py;
			if (x == 0)
				dir = 1;
			else
				dir = -1;
			//vel = FP.rand(40) + 10;
			vel = 200;
			mask = new Pixelmask(REDENEMY_IMG);
			type = "RedEnemy";			
		}
		
		override public function update():void
		{				
			if (dir == 1)
			{
				if ((x + redEnemyImg.width) < FP.screen.width)
					x += FP.elapsed * vel;
				else
					world.remove(this);
			}
			
			if (dir == -1)
			{
				if (x > 0)
					x -= FP.elapsed * vel;
				else
					world.remove(this);
			}
			
			if (collide("Player", x, y))
			{
				world.remove(this);
				
				if (Player.estado == 1)
					GameWorld.gameScore.addScore();
				else
					GameWorld.gameScore.removeScore();
			}
		}		
	}
}