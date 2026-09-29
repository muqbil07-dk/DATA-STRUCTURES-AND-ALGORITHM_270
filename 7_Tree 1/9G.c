#include <stdio.h>
#include <stdlib.h>
#define EMPTY -1
#define DELETED -2
struct dsu {
    int *parent;
    int *size;
};
struct cell {
    int row;
    int col;
    int representative;
    int rowPrevious;
    int rowNext;
    int colPrevious;
    int colNext;
    int hashNext;
    int active;
};
struct addedEdge {
    int u;
    int v;
};
struct heapItem {
    int row;
    int size;
};
struct dsu firstForest;
struct dsu secondForest;
struct cell *cells;
int cellCount;
int *rowHead;
int *colHead;
int *rowCellCount;
int *colCellCount;
int *rowParent;
int *colParent;
int *hashHead;
int hashSize;
int hashMask;
struct heapItem *heap;
int heapSize;

void pushHeap(int row, int size);

void initDsu(struct dsu *set, int n) {
    int i;

    set->parent = (int *)malloc((n + 1) * sizeof(int));
    set->size = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++) {
        set->parent[i] = i;
        set->size[i] = 1;
    }
}

int findRoot(struct dsu *set, int value) {
    if (set->parent[value] != value) {
        set->parent[value] = findRoot(set, set->parent[value]);
    }
    return set->parent[value];
}

void unite(struct dsu *set, int first, int second) {
    int rootFirst;
    int rootSecond;
    int temp;

    rootFirst = findRoot(set, first);
    rootSecond = findRoot(set, second);
    if (rootFirst == rootSecond) {
        return;
    }

    if (set->size[rootFirst] < set->size[rootSecond]) {
        temp = rootFirst;
        rootFirst = rootSecond;
        rootSecond = temp;
    }

    set->parent[rootSecond] = rootFirst;
    set->size[rootFirst] += set->size[rootSecond];
}

int pairHash(int row, int col) {
    unsigned int value;

    value = (unsigned int)row * 1000003u;
    value ^= (unsigned int)col * 9176u;
    value ^= value >> 16;
    return (int)(value & (unsigned int)hashMask);
}

int findCell(int row, int col) {
    int position;
    int current;

    position = pairHash(row, col);
    current = hashHead[position];
    while (current != -1) {
        if (cells[current].row == row && cells[current].col == col
                && cells[current].active) {
            return current;
        }
        current = cells[current].hashNext;
    }
    return -1;
}

void putCell(int row, int col, int value) {
    int position;

    position = pairHash(row, col);
    cells[value].hashNext = hashHead[position];
    hashHead[position] = value;
}

void deleteCell(int row, int col) {
    int position;
    int current;
    int previous;

    position = pairHash(row, col);
    current = hashHead[position];
    previous = -1;
    while (current != -1) {
        if (cells[current].row == row && cells[current].col == col
                && cells[current].active) {
            if (previous == -1) {
                hashHead[position] = cells[current].hashNext;
            } else {
                cells[previous].hashNext = cells[current].hashNext;
            }
            cells[current].hashNext = -1;
            return;
        }
        previous = current;
        current = cells[current].hashNext;
    }
}

void addToRow(int row, int cellNumber) {
    cells[cellNumber].rowPrevious = -1;
    cells[cellNumber].rowNext = rowHead[row];
    if (rowHead[row] != -1) {
        cells[rowHead[row]].rowPrevious = cellNumber;
    }
    rowHead[row] = cellNumber;
    rowCellCount[row]++;
}

void addToColumn(int col, int cellNumber) {
    cells[cellNumber].colPrevious = -1;
    cells[cellNumber].colNext = colHead[col];
    if (colHead[col] != -1) {
        cells[colHead[col]].colPrevious = cellNumber;
    }
    colHead[col] = cellNumber;
    colCellCount[col]++;
}

void removeFromRow(int row, int cellNumber) {
    int previous;
    int nextCell;

    previous = cells[cellNumber].rowPrevious;
    nextCell = cells[cellNumber].rowNext;
    if (previous == -1) {
        rowHead[row] = nextCell;
    } else {
        cells[previous].rowNext = nextCell;
    }
    if (nextCell != -1) {
        cells[nextCell].rowPrevious = previous;
    }
    rowCellCount[row]--;
}

void removeFromColumn(int col, int cellNumber) {
    int previous;
    int nextCell;

    previous = cells[cellNumber].colPrevious;
    nextCell = cells[cellNumber].colNext;
    if (previous == -1) {
        colHead[col] = nextCell;
    } else {
        cells[previous].colNext = nextCell;
    }
    if (nextCell != -1) {
        cells[nextCell].colPrevious = previous;
    }
    colCellCount[col]--;
}

void deleteCellRecord(int cellNumber) {
    int row;
    int col;

    row = cells[cellNumber].row;
    col = cells[cellNumber].col;
    deleteCell(row, col);
    removeFromRow(row, cellNumber);
    removeFromColumn(col, cellNumber);
    cells[cellNumber].active = 0;
}

void moveCellToRow(int cellNumber, int newRow) {
    int oldRow;
    int col;

    oldRow = cells[cellNumber].row;
    col = cells[cellNumber].col;
    deleteCell(oldRow, col);
    removeFromRow(oldRow, cellNumber);
    removeFromColumn(col, cellNumber);
    cells[cellNumber].row = newRow;
    addToRow(newRow, cellNumber);
    addToColumn(col, cellNumber);
    putCell(newRow, col, cellNumber);
}

void moveCellToColumn(int cellNumber, int newCol) {
    int row;
    int oldCol;

    row = cells[cellNumber].row;
    oldCol = cells[cellNumber].col;
    deleteCell(row, oldCol);
    removeFromRow(row, cellNumber);
    removeFromColumn(oldCol, cellNumber);
    cells[cellNumber].col = newCol;
    addToRow(row, cellNumber);
    addToColumn(newCol, cellNumber);
    putCell(row, newCol, cellNumber);
}

void mergeRows(int larger, int smaller) {
    int current;
    int nextCell;
    int col;
    int existing;

    current = rowHead[smaller];
    while (current != -1) {
        nextCell = cells[current].rowNext;
        col = cells[current].col;
        existing = findCell(larger, col);
        if (existing != -1) {
            deleteCellRecord(current);
        } else {
            moveCellToRow(current, larger);
        }
        current = nextCell;
    }

    rowParent[smaller] = larger;
}

void mergeColumns(int larger, int smaller) {
    int current;
    int nextCell;
    int row;
    int existing;

    current = colHead[smaller];
    while (current != -1) {
        nextCell = cells[current].colNext;
        row = cells[current].row;
        existing = findCell(row, larger);
        if (existing != -1) {
            deleteCellRecord(current);
            pushHeap(row, rowCellCount[row]);
        } else {
            moveCellToColumn(current, larger);
        }
        current = nextCell;
    }

    colParent[smaller] = larger;
}

void pushHeap(int row, int size) {
    int position;
    struct heapItem item;

    heapSize++;
    position = heapSize;
    heap[position].row = row;
    heap[position].size = size;

    while (position > 1 && heap[position / 2].size < heap[position].size) {
        item = heap[position / 2];
        heap[position / 2] = heap[position];
        heap[position] = item;
        position = position / 2;
    }
}

struct heapItem popHeap(void) {
    struct heapItem result;
    struct heapItem last;
    int position;
    int child;

    result = heap[1];
    last = heap[heapSize];
    heapSize--;
    if (heapSize == 0) {
        return result;
    }

    position = 1;
    while (position * 2 <= heapSize) {
        child = position * 2;
        if (child + 1 <= heapSize
                && heap[child + 1].size > heap[child].size) {
            child++;
        }
        if (heap[child].size <= last.size) {
            break;
        }
        heap[position] = heap[child];
        position = child;
    }
    heap[position] = last;
    return result;
}

int validHeapItem(struct heapItem item, int excludedRow) {
    return rowParent[item.row] == item.row
        && rowCellCount[item.row] == item.size
        && item.row != excludedRow;
}

int takeBestRow(int excludedRow) {
    struct heapItem item;

    while (heapSize > 0) {
        item = popHeap();
        if (validHeapItem(item, excludedRow)) {
            return item.row;
        }
    }
    return -1;
}

int main(void) {
    int n;
    int m1;
    int m2;
    int i;
    int u;
    int v;
    int temp;
    int root1;
    int root2;
    int current;
    int chosenA;
    int chosenB;
    int firstRow;
    int secondRow;
    int firstColumn;
    int secondColumn;
    int activeRows;
    int originalM1;
    int originalM2;
    struct addedEdge *answer;
    int answerCount;
    struct dsu swapped;

    scanf("%d %d %d", &n, &m1, &m2);
    originalM1 = m1;
    originalM2 = m2;
    initDsu(&firstForest, n);
    initDsu(&secondForest, n);

    while (m1--) {
        scanf("%d %d", &u, &v);
        unite(&firstForest, u, v);
    }
    while (m2--) {
        scanf("%d %d", &u, &v);
        unite(&secondForest, u, v);
    }

    if (originalM1 < originalM2) {
        swapped = firstForest;
        firstForest = secondForest;
        secondForest = swapped;
    }

    rowParent = (int *)malloc((n + 1) * sizeof(int));
    colParent = (int *)malloc((n + 1) * sizeof(int));
    rowHead = (int *)malloc((n + 1) * sizeof(int));
    colHead = (int *)malloc((n + 1) * sizeof(int));
    rowCellCount = (int *)calloc(n + 1, sizeof(int));
    colCellCount = (int *)calloc(n + 1, sizeof(int));
    cells = (struct cell *)malloc((n + 1) * sizeof(struct cell));

    for (i = 1; i <= n; i++) {
        rowParent[i] = i;
        colParent[i] = i;
        rowHead[i] = -1;
        colHead[i] = -1;
    }

    hashSize = 1;
    while (hashSize < 8 * (n + 1)) {
        hashSize = hashSize * 2;
    }
    hashMask = hashSize - 1;
    hashHead = (int *)malloc(hashSize * sizeof(int));
    for (i = 0; i < hashSize; i++) {
        hashHead[i] = -1;
    }

    cellCount = 0;
    for (i = 1; i <= n; i++) {
        root1 = findRoot(&firstForest, i);
        root2 = findRoot(&secondForest, i);
        if (findCell(root1, root2) == -1) {
            cells[cellCount].row = root1;
            cells[cellCount].col = root2;
            cells[cellCount].representative = i;
            cells[cellCount].active = 1;
            addToRow(root1, cellCount);
            addToColumn(root2, cellCount);
            putCell(root1, root2, cellCount);
            cellCount++;
        }
    }

    heap = (struct heapItem *)malloc((4 * n + 10) * sizeof(struct heapItem));
    heapSize = 0;
    for (i = 1; i <= n; i++) {
        if (findRoot(&firstForest, i) == i) {
            pushHeap(i, rowCellCount[i]);
        }
    }

    answer = (struct addedEdge *)malloc((n + 1) * sizeof(struct addedEdge));
    answerCount = 0;
    activeRows = 0;
    for (i = 1; i <= n; i++) {
        if (rowParent[i] == i && rowCellCount[i] > 0) {
            activeRows++;
        }
    }

    while (activeRows > 1) {
        firstRow = takeBestRow(-1);
        secondRow = takeBestRow(firstRow);
        if (firstRow == -1 || secondRow == -1) {
            break;
        }

        if (rowCellCount[firstRow] < rowCellCount[secondRow]) {
            temp = firstRow;
            firstRow = secondRow;
            secondRow = temp;
        }

        chosenA = rowHead[firstRow];
        chosenB = rowHead[secondRow];
        if (cells[chosenA].col == cells[chosenB].col) {
            current = cells[chosenA].rowNext;
            if (current != -1) {
                chosenA = current;
            } else {
                current = cells[chosenB].rowNext;
                if (current != -1) {
                    chosenB = current;
                }
            }
        }

        if (cells[chosenA].col == cells[chosenB].col) {
            break;
        }

        answer[answerCount].u = cells[chosenA].representative;
        answer[answerCount].v = cells[chosenB].representative;
        answerCount++;
        firstColumn = cells[chosenA].col;
        secondColumn = cells[chosenB].col;

        if (colCellCount[firstColumn] < colCellCount[secondColumn]) {
            temp = firstColumn;
            firstColumn = secondColumn;
            secondColumn = temp;
        }

        mergeRows(firstRow, secondRow);
        mergeColumns(firstColumn, secondColumn);
        rowParent[secondRow] = firstRow;
        activeRows--;
        pushHeap(firstRow, rowCellCount[firstRow]);
    }

    printf("%d\n", answerCount);
    for (i = 0; i < answerCount; i++) {
        printf("%d %d\n", answer[i].u, answer[i].v);
    }

    free(firstForest.parent);
    free(firstForest.size);
    free(secondForest.parent);
    free(secondForest.size);
    free(rowParent);
    free(colParent);
    free(rowHead);
    free(colHead);
    free(rowCellCount);
    free(colCellCount);
    free(cells);
    free(hashHead);
    free(heap);
    free(answer);
    return 0;
}

