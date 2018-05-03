#include<sstream>
#include "menu.h"
#include "imageFactory.h"

Menu::Menu(SDL_Renderer* rend) :
  renderer(rend),
  gdata(Gamedata::getInstance()),
  hudFrame( {gdata.getXmlInt("menu/loc/x"),
             gdata.getXmlInt("menu/loc/y"),
             gdata.getXmlInt("menu/width"),
             gdata.getXmlInt("menu/height")}
  ),
  menuColor({static_cast<Uint8>(gdata.getXmlInt("menu/color/r")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/g")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/b")),
             static_cast<Uint8>(gdata.getXmlInt("menu/color/a"))}
  ),
  clock( Clock::getInstance() ),
  io( IoMod::getInstance() ),
  options(),
  titleLoc( { gdata.getXmlInt("menu/titleLoc/x"),
	      gdata.getXmlInt("menu/titleLoc/y")}
	   ),
  textLoc( { gdata.getXmlInt("menu/textLoc/x"),
		gdata.getXmlInt("menu/textLoc/y")}
	     ),
  optionLoc( { gdata.getXmlInt("menu/optionLoc/x"),
               gdata.getXmlInt("menu/optionLoc/y")}
           ),
  clicks( {new Sprite("clickOff"), new Sprite("clickOn")} ),
  backimage( ImageFactory::getInstance().getImage("menuBackground")),
  currentClick(0),
  currentOption(0),
  spaces(gdata.getXmlInt("menu/spaces")),
  startClickX(optionLoc[0]-spaces),
  startClickY(optionLoc[1]+spaces),
  clickX(startClickX),
  clickY(startClickY)
{
  int noOfOptions = gdata.getXmlInt("menu/noOfOptions");
  std::stringstream strm;
  for (int i = 0; i < noOfOptions; ++i) {
    strm.clear();
    strm.str("");
    strm << i;
    std::string option("menu/option"+strm.str());
    options.push_back(gdata.getXmlStr(option));
  }
}

void Menu::incrIcon() {
  clickY += spaces;
  if ( clickY > static_cast<int>(options.size())*spaces+optionLoc[1]) {
    clickY = startClickY;
    currentOption = 0;
  }
  else ++currentOption;
}

void Menu::decrIcon() {
  clickY -= spaces;
  if ( clickY < spaces+optionLoc[1]) {
    clickY = startClickY+spaces;
    currentOption = options.size()-1;
  }
  else --currentOption;
}

void Menu::draw(bool gameWon, bool gameLost) const {
  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // Set the hud background color:
  SDL_SetRenderDrawColor( renderer, 109, 116, 123, .9*255 );

  // Draw the filled rectangle:
  SDL_RenderFillRect( renderer, &hudFrame );

  backimage->draw(0,0,hudFrame.x+20,hudFrame.y+15);

  io.writeText("Tim The Ferocious Fire Spirit", titleLoc[0], titleLoc[1]);

  if( gameWon ){
    io.writeText("Congratulations! Your Power Grows!", textLoc[0]+70, textLoc[1]);
  }
  else if( gameLost ){
    io.writeText("Game Over! Your Fire Has Gone Out...", textLoc[0]+75, textLoc[1]);
  }
  else {
    io.writeText("Prove yourself to the Wizard and receive a gift", textLoc[0], textLoc[1]);
    io.writeText("But never kill the innocent...", textLoc[0]+100, textLoc[1]+spaces);
    io.writeText("And be weary:", textLoc[0]+220, textLoc[1]+2.5*spaces);
    io.writeText("Those that take to the air don't care", textLoc[0]+70, textLoc[1]+3.5*spaces);
  }

  int space = spaces;
  for ( const std::string& option : options ) {
    io.writeText(option, optionLoc[0], optionLoc[1]+space);
    space += spaces;
  }
  // We have to draw the clickOn & clickOff relative to the screen,
  // and we don't want to offset by the location of the viewprot:
  clicks[currentClick]->getImage()->draw(0, 0, clickX, clickY);
}
