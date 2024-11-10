#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>
#include <string.h>
#include <stdlib.h>

// Define strdup function for compatibility
char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

typedef enum {
    ALL = 0,
    PENDING,
    COMPLETED,
} entry_filter;

typedef struct task_entry {
    char* desc;
    char* date;
    bool completed;
    struct task_entry* next;  // Pointer to the next task entry
} task_entry;

#define WIN_MARGIN 20.0f

static int winw = 1280, winh = 720;
static LfFont titlefont, smallfont;
static entry_filter current_filter = ALL;
static task_entry* head = NULL;  // Head of the linked list
static LfTexture removetexture;

// Declare the Topbar function before main
static void Topbar();

// Function to add a new task entry to the linked list
static void add_task(const char* desc, const char* date) {
    task_entry* new_entry = (task_entry*)malloc(sizeof(task_entry));
    new_entry->desc = strdup(desc);  // Copy the description
    new_entry->date = strdup(date);  // Copy the date
    new_entry->completed = false;
    new_entry->next = NULL;

    if (head == NULL) {
        head = new_entry;  // Set as the first task if the list is empty
    } else {
        task_entry* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_entry;  // Append to the end of the list
    }
}

// Function to delete a task entry
void delete_task(task_entry* task_to_delete) {
    if (head == NULL || task_to_delete == NULL) return;

    // If the task to delete is the head of the list
    if (head == task_to_delete) {
        task_entry* temp = head;
        head = head->next;  // Set the head to the next task
        free(temp->desc);
        free(temp->date);
        free(temp);
        return;
    }

    // Find the task in the list
    task_entry* current = head;
    while (current->next != NULL && current->next != task_to_delete) {
        current = current->next;
    }

    if (current->next == task_to_delete) {
        task_entry* temp = current->next;
        current->next = current->next->next;
        free(temp->desc);
        free(temp->date);
        free(temp);
    }
}

// Function to categorize tasks based on filter
static void categorize() {
    const uint32_t filter_count = 3;
    static const char* filter_options[] = {"All", "Pending", "Completed"};

    LfUIElementProps props = lf_get_theme().text_props;
    props.margin_top = 15.0f;
    props.margin_left = 10.0f;
    props.margin_right = 10.0f;
    props.padding = 10.0f;
    props.border_width = 0.0f;
    props.corner_radius = 8.0f;
    props.color = LF_NO_COLOR;
    props.text_color = LF_WHITE;

    float width = 0.0f;
    float ptrx_before = lf_get_ptr_x();
    float ptry_before = lf_get_ptr_y();
    lf_push_style_props(props);
    lf_set_no_render(true);
    lf_set_ptr_y_absolute(lf_get_ptr_y() + 30.0f);

    for (uint32_t i = 0; i < filter_count; i++) {
        lf_button(filter_options[i]);
    }
    lf_set_no_render(false);
    lf_set_ptr_y_absolute(ptry_before);

    width = lf_get_ptr_x() - ptrx_before - props.margin_right - props.padding;
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 3.0f);

    lf_set_line_should_overflow(false);
    for (uint32_t i = 0; i < filter_count; i++) {
        props.color = (current_filter == i) ? (LfColor){65, 167, 204, 255} : LF_NO_COLOR;
        lf_push_style_props(props);
        if (lf_button(filter_options[i]) == LF_CLICKED) {
            current_filter = (entry_filter)i;
        }
        lf_pop_style_props();
    }
    lf_set_line_should_overflow(true);
}

// Topbar function
static void Topbar() {
    lf_push_font(&titlefont);
    lf_text("Todo-App");
    lf_pop_font();

    const float width = 140.0f;
    lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 3.0f);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    props.color = (LfColor){65, 167, 204, 255};
    props.border_width = 0.0f;
    props.corner_radius = 4.0f;
    lf_push_style_props(props);
    lf_set_line_should_overflow(false);
    lf_button_fixed("Add Task", width, -1);
    lf_set_line_should_overflow(true);
    lf_pop_style_props();
}

// Main function
int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(winw, winh, "Todo-App", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    lf_init_glfw(winw, winh, window);

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter-bold.ttf", 35.0f);
    smallfont = lf_load_font("./fonts/inter.ttf", 35.0f / 2);
    removetexture = lf_load_texture("./icons/remove.png", true, LF_TEX_FILTER_LINEAR);

    // Add some initial tasks to the linked list
    for (uint32_t i = 0; i < 5; i++) {
        add_task("New doc in C", "nothing");
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        lf_begin();
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}),
                     ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), true);

        Topbar();
        lf_next_line();
        categorize();
        lf_next_line();

        // Check if there are no tasks
        if (head == NULL) {
            // Display "No tasks added"
            LfUIElementProps props = lf_get_theme().text_props;
            props.margin_top = 30.0f;
            props.margin_left = 10.0f;
            props.text_color = LF_WHITE;
            lf_push_style_props(props);
            lf_text("No tasks added");
            lf_pop_style_props();
        } else {
            // Loop through each task entry in the linked list
            for (task_entry* entry = head; entry != NULL; entry = entry->next) {
                // Only display tasks based on the current filter
                if (current_filter == ALL || (current_filter == PENDING && !entry->completed) || (current_filter == COMPLETED && entry->completed)) {
                    // Delete button for each entry
                    {
                        LfUIElementProps props = lf_get_theme().button_props;
                        props.color = LF_NO_COLOR;
                        props.border_width = 0.0f;
                        props.padding = 0.0f;
                        props.margin_top = 30.0f;
                        props.margin_left = 40.0f;
                        lf_push_style_props(props);

                        if (lf_image_button(((LfTexture){.id = removetexture.id, .width = 20, .height = 20})) == LF_CLICKED) {
                            delete_task(entry);  // Call delete function when the button is clicked
                            break;  // Exit after deleting to avoid accessing deleted memory
                        }

                        lf_pop_style_props();
                    }

                    // Checkbox for each entry
                    {
                        LfUIElementProps props = lf_get_theme().checkbox_props;
                        props.border_width = 1.0f;
                        props.corner_radius = 0;
                        props.margin_top = 30;
                        props.padding = 5.0f;
                        props.margin_left = 5.0f;
                        props.color = LF_BLACK;
                        lf_push_style_props(props);
                        if (lf_checkbox("", &entry->completed, LF_NO_COLOR, ((LfColor){65, 167, 204, 255})) == LF_CLICKED) {
                            // Checkbox click logic here
                        }
                        lf_pop_style_props();
                    }

                    // Display entry description and date
                    lf_push_font(&smallfont);
                    {
                        LfUIElementProps props = lf_get_theme().text_props;
                        props.margin_top = 30.0f;
                        props.margin_left = 5.0f;
                        props.text_color = LF_WHITE;
                        lf_push_style_props(props);

                        float descptr_x = lf_get_ptr_x();
                        lf_text(entry->desc);

                        lf_set_ptr_x_absolute(descptr_x);
                        lf_set_ptr_y_absolute(lf_get_ptr_y() + smallfont.font_size);
                        props.text_color = (LfColor){150, 150, 150, 255};
                        lf_push_style_props(props);
                        lf_text(entry->date);
                        lf_next_line();
                        lf_pop_style_props();
                    }
                    lf_pop_font();
                }
            }
        }

        lf_div_end();
        lf_end();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
