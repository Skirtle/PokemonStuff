from fastapi import FastAPI
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles

from engine import get_pokemon_from_query
from pokemon import create_database_from_csv

app = FastAPI()
ALL_POKEMON = create_database_from_csv()
MAX_RESULTS = 100

app.mount("/images", StaticFiles(directory = "./sprites-master/sprites/pokemon/other/official-artwork"), name = "images")

@app.get("/search")
async def search(query: str = ""):
    if (query == ""): valid_pokemon = ALL_POKEMON[:]
    else: valid_pokemon = get_pokemon_from_query(ALL_POKEMON, query)
    
    return {
        "count": len(valid_pokemon),
        "results": [p.serialized() for p in valid_pokemon]
    }
    
@app.get("/", response_class = HTMLResponse)
async def homepage() -> str:
    s = ""
    with open("homepage.html", "r") as file:
        for line in file:
            s += line
    return s