
int main(void) {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1000, 1000, "yarl");
    while (!WindowShouldClose()) {
        BeginDrawing();
        yarl_render_raylib(yarl, 50, 50, 1);
        EndDrawing();
    }
    CloseWindow();
}
