#ifndef MAIN
#define MAIN

#include "coordinate.h"
#include "city.hpp"
#include "building.hpp"
#include "car.hpp"
#include "intersection.hpp"
#include "coordinate.h"
#include "road.hpp"
#include "person.hpp"
#include "global.h"
#include "city_environment.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <vector>
#include <fstream>


void drawElements(sf::RenderWindow& window, const std::vector<sf::Vector2i>& positions, 
                  const sf::Texture& texture, float scale, const sf::Color& color) {
    for (const auto& position : positions) {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(position.x * SCALE, position.y * SCALE);
        sprite.setScale(scale / texture.getSize().x, scale / texture.getSize().y);
        sprite.setColor(color);
        window.draw(sprite);
    }
}

void displayBarChart(std::vector<int> rawData, const std::string& day, long hoursElapsed) {
    const int windowWidth = 650;
    const int windowHeight = 400;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Traffic Daily Analysis");

    const float barWidth = 15.0f;
    const float spaceBetweenBars = 5.0f;
    const float chartHeight = 300.0f;
    const float offsetX = 80.0f;
    const float offsetY = 50.0f;

    auto dayPast = hoursElapsed / 24;
    auto hourPastInDay = hoursElapsed % 24;
    std::vector<float> data(rawData.size());
    
    for (int i = 0; i < 24; i++) {
        if (dayPast <= 0) {
            data[i] = rawData[i];
        } else {
            data[i] = i < hourPastInDay ? rawData[i] *1.0f / (dayPast + 1) : rawData[i] *1.0f / (dayPast);  
        }
    }

    // Calculate the maximum value and the average
    int maxValue = 0;
    int sum = 0;
    for (const auto& value : data) {
        if (value > maxValue) {
            maxValue = value;
        }
        sum += value;
    }
   

    float average = sum * 1.0f / 24;
    float scaleY = (maxValue > 0) ? chartHeight / maxValue : 1.0f;

    sf::Font font;
    if (!font.loadFromFile("assets/Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Draw x-axis and y-axis
        sf::RectangleShape xAxis(sf::Vector2f(windowWidth - 2 * offsetX + 40, 2.0f));
        xAxis.setFillColor(sf::Color::Black);
        xAxis.setPosition(offsetX, windowHeight - offsetY);
        window.draw(xAxis);

        sf::RectangleShape yAxis(sf::Vector2f(2.0f, chartHeight));
        yAxis.setFillColor(sf::Color::Black);
        yAxis.setPosition(offsetX, windowHeight - offsetY - chartHeight);
        window.draw(yAxis);

        // X-axis label
        sf::Text xAxisLabel("Hours per day (0-23)", font, 16);
        xAxisLabel.setFillColor(sf::Color::Black);
        xAxisLabel.setPosition(windowWidth / 2.0f - 70, windowHeight - offsetY + 20);
        window.draw(xAxisLabel);

        // Y-axis label
        sf::Text yAxisLabel("Number of cars", font, 16);
        yAxisLabel.setFillColor(sf::Color::Black);
        yAxisLabel.setRotation(-90.0f);
        yAxisLabel.setPosition(offsetX - 55, windowHeight / 2.0f + 45);
        window.draw(yAxisLabel);

        // Draw bars and labels
        int index = 0;
        for (const auto& value : data) {
            sf::RectangleShape bar(sf::Vector2f(barWidth, -value * scaleY));
            bar.setFillColor(sf::Color::Blue);
            bar.setPosition(offsetX + index * (barWidth + spaceBetweenBars), windowHeight - offsetY);
            window.draw(bar);

            sf::Text keyLabel(std::to_string(index), font, 12);
            keyLabel.setFillColor(sf::Color::Black);
            keyLabel.setPosition(offsetX + index * (barWidth + spaceBetweenBars) + barWidth / 2 - 5, windowHeight - offsetY + 5);
            window.draw(keyLabel);

            ++index;
        }


        // Display average value
        std::ostringstream avgStream;
        avgStream.precision(2);
        avgStream << std::fixed << average;
        sf::Text avgText("Avg: " + avgStream.str(), font, 14);
        avgText.setFillColor(sf::Color::Red);
        avgText.setPosition(windowWidth - 80, windowHeight - offsetY - average * scaleY - 20);
        window.draw(avgText);


        // Display grid lines
        int markerStep = maxValue / 10;
        if (markerStep == 0) markerStep = 1;
        for (int i = 0; i <= maxValue; i += markerStep) {
            sf::Text marker(std::to_string(i), font, 12);
            marker.setFillColor(sf::Color::Black);
            marker.setPosition(offsetX - 15, windowHeight - offsetY - i * scaleY - 10);
            window.draw(marker);

            sf::RectangleShape markerLine(sf::Vector2f(windowWidth - 2 * offsetX + 40, 1.0f));
            markerLine.setFillColor(sf::Color(200, 200, 200));
            markerLine.setPosition(offsetX, windowHeight - offsetY - i * scaleY);
            window.draw(markerLine);
        }

        sf::RectangleShape avgLine(sf::Vector2f(windowWidth - 2 * offsetX + 40, 1.0f));
        avgLine.setFillColor(sf::Color::Red);
        avgLine.setPosition(offsetX, windowHeight - offsetY - average * scaleY);
        window.draw(avgLine);

        window.display();
    }
}


sf::Color interpolateColor(const sf::Color& color1, const sf::Color& color2, float factor) 
    {
        return sf::Color(
            static_cast<sf::Uint8>(color1.r + factor * (color2.r - color1.r)),
            static_cast<sf::Uint8>(color1.g + factor * (color2.g - color1.g)),
            static_cast<sf::Uint8>(color1.b + factor * (color2.b - color1.b))
        );
    };

auto colorLambda = [](int x) -> sf::Color {
    int r = std::round(-0.9256 * x * x + 20.845 * x + 117.0423);
    int g = std::round(-1.5265 * x * x + 34.666 * x + 96.8654);
    int b = std::round(-0.7558 * x * x + 16.1568 * x + 229.9462);

    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);

    return sf::Color(r, g, b);
};

struct AnimatedSprite {
    sf::Sprite sprite;
    sf::Clock animationClock;
    sf::Clock movementClock;
    int currentFrame = 0;
    bool movingRight = true;
    float leftBound;
    float rightBound;
    float moveSpeed = 40.0f; // Movement speed in pixels per second
    sf::Vector2f initialPosition;
};

// Initialize the sprites with different positions
std::vector<AnimatedSprite> initializeAnimatedSprites(sf::Texture& spriteSheet, const std::vector<sf::Vector2f>& positions, float frameWidth, float frameHeight) {
    std::vector<AnimatedSprite> sprites;

    for (const auto& pos : positions) {
        AnimatedSprite animSprite;
        animSprite.sprite.setTexture(spriteSheet);
        animSprite.sprite.setScale(0.5f, 0.5f); // Scale for all sprites
        animSprite.sprite.setPosition(pos);
        animSprite.leftBound = 13 * SCALE; // Define movement bounds
        animSprite.rightBound = 16 * SCALE;
        animSprite.initialPosition = pos;
        sprites.push_back(animSprite);
    }

    return sprites;
}

void updateAndDrawSprites(std::vector<AnimatedSprite>& sprites, sf::RenderWindow& window, float frameWidth, float frameHeight, int frameCount, float frameDuration) {
    for (auto& animSprite : sprites) {
        // Update animation
        if (animSprite.animationClock.getElapsedTime().asSeconds() >= frameDuration) {
            animSprite.animationClock.restart();
            animSprite.currentFrame = (animSprite.currentFrame + 1) % frameCount;
        }

        int left = animSprite.currentFrame * frameWidth;
        animSprite.sprite.setTextureRect(sf::IntRect(left, 0, frameWidth, frameHeight));

        // Update movement
        float deltaTime = animSprite.movementClock.restart().asSeconds();
        float movement = (animSprite.movingRight ? animSprite.moveSpeed : -animSprite.moveSpeed) * deltaTime;
        animSprite.sprite.move(movement, 0);

        if (animSprite.sprite.getPosition().x >= animSprite.rightBound && animSprite.movingRight) {
            animSprite.movingRight = false;
            animSprite.sprite.setScale(-0.5f, 0.5f); // Flip sprite to face left
            animSprite.sprite.setPosition(animSprite.rightBound, animSprite.sprite.getPosition().y);
        } else if (!animSprite.movingRight && animSprite.sprite.getPosition().x <= animSprite.leftBound) {
            animSprite.movingRight = true;
            animSprite.sprite.setScale(0.5f, 0.5f); // Flip sprite to face right
            animSprite.sprite.setPosition(animSprite.leftBound, animSprite.sprite.getPosition().y);
        }

        // Draw the sprite
        window.draw(animSprite.sprite);
    }
}


/**
 * @brief Represents a streetlight with dynamic lighting frames based on the time of day.
 */
struct StreetLight {
    /**
     * @brief Sprite object representing the streetlight.
     */
    sf::Sprite sprite;

    /**
     * @brief Total number of frames in the streetlight texture.
     */
    int frameCount = 6;

    /**
     * @brief Width of each individual frame in the streetlight texture.
     */
    int frameWidth = 9;

    /**
     * @brief Height of each individual frame in the streetlight texture.
     */
    int frameHeight = 16;

    /**
     * @brief Constructs a StreetLight object.
     *
     * Initializes the streetlight sprite with the specified texture and position.
     * Centers the sprite based on its frame dimensions.
     *
     * @param texture The texture containing the streetlight frames.
     * @param position The position to place the streetlight on the screen.
     */
    StreetLight(const sf::Texture& texture, sf::Vector2f position) {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        sprite.setPosition(position);
        sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
    }

    /**
     * @brief Updates the lighting frame of the streetlight based on the time of day.
     *
     * Determines the appropriate frame index to represent the brightness of the streetlight.
     *
     * @param timeInHour The current hour (0-23) of the day.
     */
    void update(int timeInHour) {
        int frameIndex = 0;
        if (timeInHour >= 18 || timeInHour <= 5) {
            frameIndex = 5; // Brightest frame (nighttime)
        } else if (timeInHour >= 6 && timeInHour <= 8) {
            frameIndex = 4; // Transition to morning, bright
        } else if (timeInHour >= 9 && timeInHour <= 11) {
            frameIndex = 2; // Morning, medium brightness
        } else if (timeInHour >= 12 && timeInHour <= 16) {
            frameIndex = 1; // Daytime, dimmest frame
        } else if (timeInHour >= 17) {
            frameIndex = 3; // Evening, medium brightness
        }

        sprite.setTextureRect(sf::IntRect(frameIndex * frameWidth, 0, frameWidth, frameHeight));
    }

    /**
     * @brief Renders the streetlight sprite onto the specified window.
     *
     * @param window The render window where the streetlight will be drawn.
     */
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};


std::vector<StreetLight> streetLights;

void initializeStreetLights(const sf::Texture& texture) {
    for (const auto& position : streetLightPositions) {
        streetLights.emplace_back(texture, position);
    }
}

long elapseTime = -1;
int tick = -1;
int rate = 1;
bool HIGHLIGHT_MODE = false;


int main() {
    std::string intersectionData = "../src/data/intersection.json";
    std::vector<std::shared_ptr<Intersection>> intersections = readIntersection(intersectionData);
    std::string roadData = "../src/data/road.json";
    std::vector<std::shared_ptr<Road>> roads = readRoad(roadData, intersections);
    std::string buildingData = "../src/data/building.json";
    std::vector<std::shared_ptr<Building>> buildings = readBuilding(buildingData);
    std::string personData = "../src/data/person.json";
    std::vector<std::shared_ptr<Person>> people = readPerson(personData, buildings);
    globalRoads =  roads;


    std::map<std::string, sf::Texture> lakeTextures;
    for (int i = 1; i < 19; i++){
        sf::Texture texture;
        if (!texture.loadFromFile("assets/Tiles/lake/" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load texture: " << std::to_string(i) << std::endl;
            return -1;
        }
        lakeTextures[std::to_string(i) + ".png"] = texture;
    }
    

    std::map<std::string, sf::Texture> landTextures;
    for (int i = 1; i < 11; i++){
        sf::Texture texture;
        if (!texture.loadFromFile("assets/Tiles/land/" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load texture: " << std::to_string(i) << std::endl;
            return -1;
        }
        landTextures[std::to_string(i) + ".png"] = texture;
    }

    // CITYYYYYYYYYYYYY
    std::vector<std::shared_ptr<Building>> busStops(buildings.end() - 5, buildings.end());
    
    City city = City(25, 20, 100, buildings, {}, people, roads, intersections, busStops);
    

    sf::RenderWindow window(sf::VideoMode(1200, 800), "City Visualization");
    window.setFramerateLimit(60);

    sf::Texture intersectionTexture, carTexture, treeTexture, flowerTexture, busTexture, rockTexture, forestTexture, bushTexture, mushroomTexture, shipTexture, planeTexture;
    sf::Texture roadTexture, roadTextureHighlight1, roadTextureHighlight2, roadTextureHighlight3, roadTextureHighlight4;

    if (!roadTexture.loadFromFile("assets/Tiles/road.png") ||
        !roadTextureHighlight1.loadFromFile("assets/Tiles/road_highlight_1.png") ||
        !roadTextureHighlight2.loadFromFile("assets/Tiles/road_highlight_2.png") ||
        !roadTextureHighlight3.loadFromFile("assets/Tiles/road_highlight_3.png") ||
        !roadTextureHighlight4.loadFromFile("assets/Tiles/road_highlight_4.png") ||
        !intersectionTexture.loadFromFile("assets/Tiles/intersection.png") ||
        !treeTexture.loadFromFile("assets/Tiles/environment/tree.png") ||
        !flowerTexture.loadFromFile("assets/Tiles/environment/flower.png") ||
        !busTexture.loadFromFile("assets/Tiles/bus.png") ||
        !rockTexture.loadFromFile("assets/Tiles/environment/rock.png") ||
        !forestTexture.loadFromFile("assets/Tiles/environment/forest.png") ||
        !bushTexture.loadFromFile("assets/Tiles/environment/bush.png") ||
        !mushroomTexture.loadFromFile("assets/Tiles/environment/mushroom.png") ||
        !shipTexture.loadFromFile("assets/Tiles/environment/ship.png") ||
        !planeTexture.loadFromFile("assets/Tiles/environment/plane.png") 
        ) {
        std::cerr << "Failed to load textures!" << std::endl;
        return -1;
    }
    sf::Texture streetLightTexture;
    if (!streetLightTexture.loadFromFile("assets/Tiles/environment/streetlight_sprite_sheet.png")) {
        std::cerr << "Failed to load streetlight sprite sheet!" << std::endl;
        return -1;
    }
    initializeStreetLights(streetLightTexture);


    std::vector<sf::Texture> carTextures;
    for (int i = 1; i <= 5; ++i) { 
        sf::Texture texture;
        if (!texture.loadFromFile("assets/Tiles/car/" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load car texture: car" << i << ".png" << std::endl;
            return -1;
        }
        carTextures.push_back(texture);
}


    std::map<char, sf::Texture> buildingTextures;
    std::map<char, sf::Texture> fakeBuildingTextures;
    std::vector<char> buildingTypes = {
        'H', 'M', 'G', 'F', 'C', 'B'
    };
    for (const auto& type : buildingTypes) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/Tiles/building/" + std::string(1, type) + ".png")) {
            std::cerr << "Failed to load texture for building type: " << type << std::endl;
            return -1;
        }
        buildingTextures[type] = texture;

        sf::Texture fakeTexture;

        if (type != 'B' && !fakeTexture.loadFromFile("assets/Tiles/building/fake_" +std::string(1, type) + ".png")) {
            std::cerr << "Failed to load fake building texture for type: " << type << std::endl;
            return -1;
        }
        fakeBuildingTextures[type] = fakeTexture;

    }

    sf::Texture spriteSheet1,spriteSheet2,spriteSheet3,spriteSheet4;
    if (!spriteSheet1.loadFromFile("assets/Tiles/people/blue_man.png") ||
    !spriteSheet2.loadFromFile("assets/Tiles/people/pink_man.png") ||
    !spriteSheet3.loadFromFile("assets/Tiles/people/yellow_man.png") ||
    !spriteSheet4.loadFromFile("assets/Tiles/people/frog_man.png") 
    ) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
        return -1;
    }


    // Initialize animated sprites
    std::vector<AnimatedSprite> BlueSprites = initializeAnimatedSprites(spriteSheet1, BluePositions, frameWidth, frameHeight);
    std::vector<AnimatedSprite> PinkSprites = initializeAnimatedSprites(spriteSheet2, PinkPositions, frameWidth, frameHeight);
    std::vector<AnimatedSprite> YellowSprites = initializeAnimatedSprites(spriteSheet3, YellowPositions, frameWidth, frameHeight);
    std::vector<AnimatedSprite> FrogSprites = initializeAnimatedSprites(spriteSheet4, FrogPositions, frameWidth, frameHeight);

    sf::Font font;
    font.loadFromFile("assets/cour.ttf");
    

    sf::Texture tileTexture;
    tileTexture.loadFromFile("assets/Tiles/tile.png");
    tileTexture.setRepeated(true);

    float expandedWidth = MAP_WIDTH * SCALE * 2.0f; 
    float expandedHeight = MAP_HEIGHT * SCALE * 2.0f;
    sf::RectangleShape background(sf::Vector2f(expandedWidth, expandedHeight));
    background.setTexture(&tileTexture);
    background.setTextureRect(sf::IntRect(0, 0, expandedWidth, expandedHeight));
    background.setPosition(-MAP_WIDTH * SCALE / 2.0f, -MAP_HEIGHT * SCALE / 2.0f);

    sf::Text clockText;
    clockText.setFont(font);
    clockText.setCharacterSize(24);          
    clockText.setFillColor(sf::Color::Black);
    clockText.setStyle(sf::Text::Bold);

    sf::Text dateText;
    dateText.setFont(font);
    dateText.setCharacterSize(24);          
    dateText.setFillColor(sf::Color::Black); 
    dateText.setStyle(sf::Text::Bold);

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Black); 
    infoText.setStyle(sf::Text::Bold);
    infoText.setString("[H] Highlight traffic\t[P] Pause\t[Right click roads] Analyze\t[Zoom & pan] Explore");
    infoText.setPosition(10, window.getSize().y - 70);
    sf::FloatRect textBounds = infoText.getLocalBounds();
    infoText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);


    sf::RectangleShape infoBackground;
    infoBackground.setSize(sf::Vector2f(window.getSize().x, 40));
    infoBackground.setFillColor(sf::Color(200, 200, 200, 150));
    infoBackground.setPosition(0, window.getSize().y - 40);

    infoText.setPosition(infoBackground.getSize().x / 2.0f, infoBackground.getPosition().y + infoBackground.getSize().y / 2.0f);

    sf::View view(sf::FloatRect(0, 0, 1200, 800));
    view.setCenter(MAP_WIDTH * SCALE / 2.0f, MAP_HEIGHT * SCALE / 2.0f);
    window.setView(view);

    sf::View uiView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    float zoomLevel = 0.8f; 
    view.zoom(zoomLevel);

    bool dragging = false;            
    sf::Vector2i lastMousePosition;
    
    bool isPaused = false;
    while (window.isOpen() ) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                dragging = true;
                lastMousePosition = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
            }
            if (dragging) {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f delta = view.getCenter() - sf::Vector2f(currentMousePosition - lastMousePosition);
                view.setCenter(delta);
                lastMousePosition = currentMousePosition;
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (event.mouseWheelScroll.delta > 0) { // Zoom in
                    view.zoom(0.9f);
                    zoomLevel *= 0.9f;
                } else if (event.mouseWheelScroll.delta < 0) { // Zoom out
                    view.zoom(1.1f);
                    zoomLevel *= 1.1f;
                }
                sf::Vector2f newMouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f offset = mouseWorldPosition - newMouseWorldPosition;
                view.move(offset);
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::P) isPaused = !isPaused;
                else if(event.key.code == sf::Keyboard::H) HIGHLIGHT_MODE = !HIGHLIGHT_MODE;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (auto [bounds, road] : city.getRoadBounds()) {
                    if (bounds.contains(mousePosition)) {
                        std::vector<int> log; 
                        log = road->getLogs();
                        long hoursElapsed = elapseTime / 60;
                        if (hoursElapsed == 0) hoursElapsed = 1; 
                        displayBarChart(log, dateText.getString(), hoursElapsed);
                        break;
                    }
                }
            }
        }
        

        if (!isPaused) {
            city.advance();
            long timeInHour = (elapseTime * rate / 60) % 24;
            long timeInMinutes = (elapseTime * rate % 60); 
            float minutesInHour = (elapseTime % 60) / 60.0f;

            int daysElapsed = elapseTime / (24 * 60);
            int currentYear = 2024; 
            int currentMonth = 1;   
            int currentDay = 1 + daysElapsed; 

            // Adjust for months (basic example without leap year handling)
            while (currentDay > 30) { 
                currentDay -= 30;
                currentMonth++;
                if (currentMonth > 12) {
                    currentMonth = 1;
                    currentYear++;
                }
            }

            sf::Color currentColor = colorLambda(timeInHour);
            sf::Color nextColor = colorLambda((timeInHour + 1) % 24); 
            sf::Color backgroundColor = interpolateColor(currentColor, nextColor, minutesInHour);
            background.setFillColor(backgroundColor);
            window.clear();
            window.draw(background);
            
            for (const auto& [position, textureName] : lake) {
                sf::Sprite lakeSprite;
                lakeSprite.setTexture(lakeTextures[textureName]);
                lakeSprite.setPosition(position.x * SCALE - 20, position.y * SCALE);
                lakeSprite.setScale(SCALE / lakeTextures[textureName].getSize().x * 2.0, SCALE / lakeTextures[textureName].getSize().y* 1.5);
                lakeSprite.setColor(backgroundColor); 
                window.draw(lakeSprite);
            }

            for (const auto& [position, textureName] : land) {
                sf::Sprite landSprite;
                landSprite.setTexture(landTextures[textureName]);
                landSprite.setPosition(position.x * SCALE - 20, position.y * SCALE);
                landSprite.setScale(SCALE / landTextures[textureName].getSize().x * 2.0, SCALE / landTextures[textureName].getSize().y* 1.5);
                landSprite.setColor(backgroundColor);
                window.draw(landSprite);
            }
            
            drawElements(window, treePositions, treeTexture, SCALE, backgroundColor);
            drawElements(window, flowerPositions, flowerTexture, SCALE, backgroundColor);
            drawElements(window, rockPositions, rockTexture, SCALE, backgroundColor);
            drawElements(window, forestPositions, forestTexture, SCALE, backgroundColor);
            drawElements(window, mushroomPositions, mushroomTexture, SCALE, backgroundColor);
            drawElements(window, bushPositions, bushTexture, SCALE, backgroundColor);
            drawElements(window, shipPositions, shipTexture, SCALE, backgroundColor);
            drawElements(window, planePositions, planeTexture, SCALE, backgroundColor);
            




            for (const auto& position : fakeRoadHorizontalPositions) {
                sf::Sprite roadSprite;
                roadSprite.setTexture(roadTexture);
                roadSprite.setPosition(position.x * SCALE, position.y * SCALE+1);
                roadSprite.setScale(SCALE/ roadTexture.getSize().x, SCALE / roadTexture.getSize().y);
                window.draw(roadSprite);
            }

            for (const auto& position : fakeRoadVerticalPositions) {
                sf::Sprite roadSprite;
                roadSprite.setTexture(roadTexture);
                roadSprite.setPosition(position.x * SCALE, position.y * SCALE+1);
                roadSprite.setScale(SCALE/ roadTexture.getSize().x, SCALE / roadTexture.getSize().y);
                roadSprite.setRotation(90);
                window.draw(roadSprite);
            }


            for (const auto& [position, type] : fakeBuildingPositions) {
                sf::Sprite fakeBuildingSprite;
                fakeBuildingSprite.setTexture(fakeBuildingTextures[type]);
                fakeBuildingSprite.setPosition(position.x * SCALE -30, position.y * SCALE);
                fakeBuildingSprite.setScale(SCALE / fakeBuildingTextures[type].getSize().x, SCALE / fakeBuildingTextures[type].getSize().y);
                window.draw(fakeBuildingSprite);
            }
            
            updateAndDrawSprites(BlueSprites, window, frameWidth, frameHeight, frameCount, frameDuration);
            updateAndDrawSprites(PinkSprites, window, frameWidth, frameHeight, frameCount, frameDuration);
            updateAndDrawSprites(FrogSprites, window, frameWidth, frameHeight, frameCount, frameDuration);
            updateAndDrawSprites(YellowSprites, window, frameWidth, frameHeight, frameCount, frameDuration);

            auto highlightTextures = std::vector<sf::Texture>{roadTextureHighlight1, roadTextureHighlight2, roadTextureHighlight3, roadTextureHighlight4};
            city.drawRoads(window, roadTexture, highlightTextures, SCALE);
            city.drawIntersections(window, intersectionTexture, SCALE);
            city.drawBuildings(window, buildingTextures, SCALE);
            city.drawCars(window, carTextures, SCALE, timeInHour, timeInMinutes);
            city.drawBus(window, busTexture, SCALE);
            
            for (auto& streetLight : streetLights) {
                streetLight.update(timeInHour);
            }

            for (auto& streetLight : streetLights) {
                streetLight.draw(window);
            }



            window.setView(uiView); 

            std::ostringstream timeStream,dateStream;
            timeStream << (timeInHour < 10 ? "0" : "") << timeInHour << ":"
                    << (timeInMinutes < 10 ? "0" : "") << timeInMinutes;
            clockText.setString("Time: " + timeStream.str());
            clockText.setPosition(window.getSize().x - 250, 40);
            dateStream << "Day: " << (currentDay < 10 ? "0" : "") << currentDay;
            dateText.setString(dateStream.str());
            clockText.setPosition(window.getSize().x - 270, 30);
            dateText.setPosition(window.getSize().x - 270, 70); 

            window.draw(dateText);
            window.draw(clockText);
            window.draw(infoBackground);
            window.draw(infoText);
        }
        window.setView(view);
        window.display();


    }
    writeBuilding(buildingData, buildings);
    writeIntersection(intersectionData, intersections);
    writeRoad(roadData, roads);
    writePerson(personData, people);
    
    /**
     * @brief Clears the road logs and appends new log data.
     * 
     * This section clears the existing road log file and appends new data for each road
     * to the log file.
     */
    std::string roadLogs = "../src/data/road_logs.csv";
    std::ofstream file(roadLogs, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for clearing." << std::endl;
        return 0;
    }
    file.close(); // Close the file after clearing
    for (auto road : roads) {
        road->appendLogToCSV(roadLogs);
    }

    return 0;
}
#endif

