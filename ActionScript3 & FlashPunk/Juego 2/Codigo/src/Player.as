package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	
	public class Player extends Entity
	{
		[Embed(source = "../assets/spaceship1.png")] private const PLAYER_IMG:Class;
		
		
		private var playerImg:Image;
		private var colorOrig:uint;
		public static var estado:uint;
		
		public function Player() 
		{
			playerImg = new Image(PLAYER_IMG);
			colorOrig = playerImg.color;
			//playerImg.centerOO();
			playerImg.color = 0xDD0000;
			graphic = playerImg;
			x = 300;
			y = 200;
			mask = new Pixelmask(PLAYER_IMG);
			type = "Player";
			estado = 0;
		}
		
		override public function update():void
		{
			//trace("Player updates.");
			
			playerImg.color = colorOrig;
			estado = 0;
			
			if (Input.check(Key.RIGHT))
			{
				playerImg.color = 0xDD0000;
				estado = 1;
				
				if ((x + playerImg.width) < FP.screen.width)
					x += FP.elapsed * 200;
				else
					x = FP.screen.width - playerImg.width;
			}
			
			if (Input.check(Key.LEFT))
			{
				playerImg.color = 0xDD0000;
				estado = 1;
				
				if (x > 0)
					x -= FP.elapsed * 200;
				else
					x = 0;
			}
			
			if (Input.check(Key.DOWN))
			{
				playerImg.color = 0x00DD00;
				estado = 2;
				
				if ((y + playerImg.height) < FP.screen.height)
					y += FP.elapsed * 200;
				else
					y = FP.screen.height - playerImg.height;
			}
			
			if (Input.check(Key.UP))
			{
				playerImg.color = 0x00DD00;
				estado = 2;
				
				if (y > 0)
					y -= FP.elapsed * 200;
				else
					y = 0;
			}
			
			super.update();
		}	
	}

}