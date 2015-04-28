package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	public class Portal extends Entity
	{
		[Embed(source = "Wall.png")]
		private const PORTAL_IMG:Class;
		private var portalImg:Image;
		
		public function Portal(px:Number = 0, py:Number = 0) 
		{
			portalImg = new Image(PORTAL_IMG);
			portalImg.color = 0xff00ff00;
			this.graphic = portalImg;
			this.x = px * 32;
			this.y = py * 32;
			setHitbox(portalImg.width, portalImg.height);
			type = "Portal";	
		}
		
		public override function update():void
		{
			super.update();
		}
	}

}