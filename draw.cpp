//
// Created by zacky on 8/2/2021.
//
#include "draw.h"
void draw(int students, int schools, std::map<int,std::pair<int,int>> school, std::vector<int>red, std::vector<int>green, std::vector<int>blue,std::vector<std::vector<int>> neighborsInd){
    // writes the constants
    const int posX =0, posY = 30, width = 1920, height = 1080;

    // height and width of the rectangle
    int studentHeight = width / students;
    int schoolHeight = width / schools;

    /// initializes SDL
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // creates vectors for students and schools that will hold their x,y cords
    // (x,y)
    std::vector<std::pair<int,int>> studentCord;
    std::vector<std::pair<int,int>> schoolCordTop;
    std::vector<std::pair<int,int>> schoolCordBottom;

    // draws each student in the middle
    for (int i = 0; i <students; i++){
        // x and y of the square
        int y = 500;
        int x = i*studentHeight;

        // add square to vector
        studentCord.emplace_back(x,y);

        // gets the rgb values
        int r = red[i];
        int g = green[i];
        int b = blue[i];

        // draws the square
        SDL_Rect Rect;

        Rect.x = x;
        Rect.y = y;
        Rect.h = studentHeight;
        Rect.w = studentHeight - 5;

        // sets color
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

        // draws rect
        SDL_RenderDrawRect(renderer, &Rect);
        SDL_RenderFillRect(renderer, &Rect);
        SDL_RenderPresent(renderer);

    }

    // draws the schools on the top
    for (int i = 0; i < schools; i++){
        // gets the cords
        int y = 0;
        int x = i*schoolHeight;

        // add square to vector
        schoolCordTop.emplace_back(x,y);

        // draws the square
        SDL_Rect Rect;

        Rect.x = x;
        Rect.y = y;
        Rect.h = schoolHeight;
        Rect.w = schoolHeight - 5;

        // sets color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // draws rect
        SDL_RenderDrawRect(renderer, &Rect);
        SDL_RenderFillRect(renderer, &Rect);
        SDL_RenderPresent(renderer);
    }

    // draws the schools on the bottom
    for (int i = 0; i < schools; i++){
        // gets the cords
        int y = 800;
        int x = i*schoolHeight;

        // add square to vector
        schoolCordBottom.emplace_back(x,y);

        // draws the square
        SDL_Rect Rect;

        Rect.x = x;
        Rect.y = y;
        Rect.h = schoolHeight;
        Rect.w = schoolHeight - 5;

        // sets color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // draws rect
        SDL_RenderDrawRect(renderer, &Rect);
        SDL_RenderFillRect(renderer, &Rect);
        SDL_RenderPresent(renderer);
    }
    // draws the og connections
    for (int i = 0; i <= students; i++){
        for (int j = 0; j <neighborsInd[i+1].size(); j++){
            // index of school
            int ind = neighborsInd[i+1][j] - students-1;

            // color
            SDL_SetRenderDrawColor(renderer, red[i], green[i], blue[i], SDL_ALPHA_OPAQUE);

            int x1 = studentCord[i].first+ (studentHeight / 2);
            int y1 = studentCord[i].second;

            int x2 = schoolCordTop[ind].first + schoolHeight / 2;
            int y2 = schoolCordTop[ind].second+(schoolHeight);

            SDL_RenderDrawLine(renderer,x1,y1,x2,y2);


        }
    }

    // draws the new "perfected" lines
    std::map<int,std::pair<int,int>>::iterator it;

    // colors for places emerald,plat, gold, ruby, bronze, white in
    // emerald being best (First place) plat second etc (white is anything worse than 5th place)
    std::vector<std::vector<int>> placesColors {{80,200, 120}, {25,64,255}, {255,215,0}, {244,17,95}, {205,127,50}, {255,255,255}};

    // from, (rank,to)
    std::multimap<int,std::pair<int,int>> need;
    for (it = school.begin(); it != school.end(); it++){
        if (it->first == 0 || it->first > students) continue;

        int rank = it->second.second;
        if (rank > 5) rank = 6;
        int r = placesColors[rank - 1][0];
        int g = placesColors[rank - 1][1];
        int b = placesColors[rank - 1][2];

        int x1 = studentCord[it->first - 1].first+ (studentHeight / 2);
        int y1 = studentCord[it->first-1].second+(studentHeight);

        int x2 = schoolCordBottom[it->second.first - students-1].first + (schoolHeight / 2);
        int y2 = schoolCordBottom[it->second.first - students-1].second;

        // adds to a map for debug
        need.emplace(it->second.first, std::make_pair(it->second.second, it->first));

        // color
        SDL_SetRenderDrawColor(renderer, red[it->first - 1], green[it->first - 1], blue[it->first - 1], SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);

        /// recolor the rectangle to its ranking color
        // draws the square
        SDL_Rect Rect;

        Rect.x = schoolCordBottom[it->second.first - students-1].first;
        Rect.y = schoolCordBottom[it->second.first - students-1].second;
        Rect.h = schoolHeight;
        Rect.w = schoolHeight - 5;

        // sets color
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

        // draws rect
        SDL_RenderDrawRect(renderer, &Rect);
        SDL_RenderFillRect(renderer, &Rect);

    }
    SDL_RenderPresent(renderer);


    SDL_Delay(100000);
}