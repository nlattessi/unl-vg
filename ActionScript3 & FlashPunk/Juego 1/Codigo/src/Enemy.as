package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	public class Enemy extends Entity
	{
		[Embed(source = "AngryBird.png")]
		private const ENEMY_IMG:Class;
		private var enemyImg:Image;
		private var velocidad:Number = 0;
		
		public function Enemy(px:Number = 0, py:Number = 0)
		{
			this.enemyImg = new Image(ENEMY_IMG);
			this.graphic = enemyImg;
			this.x = px * 16;
			this.y = py * 16;
			setHitbox(enemyImg.width, enemyImg.height);
			type = "Enemy";
			velocidad = FP.rand(200) + 100;
		}
		
		override public function update():void
		{			
			this.x += velocidad * FP.elapsed;
			if (this.x > FP.screen.width)
			{
				world.remove(this);
			}
			
			super.update();
		}
	}

}