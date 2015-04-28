package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	public class Cuadro1 extends Entity
	{
		[Embed(source = "Cuadro1.png")]
		private const CUADRO1_IMG:Class;
		private var cuadro1Img:Image;
		
		private var jumpPower:Number = 150;
		private var gravity:Number = 0.9;
		private var ySpeed:Number = 0;		
		private var onTheGround:Boolean = true;
		public var portalInf:Number = 0;
		public var portalSup:Number = 0;
		
		public function Cuadro1(px:Number = 0, py:Number = 0) 
		{
			this.cuadro1Img = new Image(CUADRO1_IMG);
			this.graphic = cuadro1Img;
			this.x = px * 16;
			this.y = py * 16;
			setHitbox(cuadro1Img.width, cuadro1Img.height);
			type = "Cuadro1";
		}
		
		public function setPortalInf(n:Number = 0):void
		{
			portalInf = n;
		}
		public function setPortalSup(n:Number = 0):void
		{
			portalSup = n;
		}
		
		override public function update():void
		{
			if (Input.check(Key.LEFT))
			{
				if (this.x > 0)
				{
					this.x -= 100 * FP.elapsed;
				}
				else
				{
					this.x = 0;
				}
			}
			
			if (Input.check(Key.RIGHT))
			{
				if ((this.x + cuadro1Img.width) < FP.screen.width)
				{
					this.x += 100 * FP.elapsed;
				}
				else
				{
					this.x = FP.screen.width - cuadro1Img.width;
				}
			}
			
			if (collide("Wall", this.x, this.y + 1))
			{
				ySpeed = 0;
				onTheGround = true;
				
				if (Input.check(Key.SPACE) && onTheGround)
				{
					ySpeed -= jumpPower;
					onTheGround = false;
				}
			}
			else
			{
				ySpeed += gravity;
			}
			
			if (Input.check(Key.DOWN) && !onTheGround)
			{
				ySpeed += gravity;
			}
			
			if (collide("Portal", this.x, this.y + 1))
			{				
				this.x = this.portalSup * 32;
				this.y = 32;
			}
			
			if (collide("Enemy", this.x, this.y))
			{
				FP.world = new GameWorld();
			}
			
			this.y += ySpeed * FP.elapsed;			
			super.update();
		}
		
	}

}