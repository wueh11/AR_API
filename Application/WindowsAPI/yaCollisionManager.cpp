#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaCollider.h"

namespace ya
{
    WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};

    void CollisionManager::Tick()
    {
        Scene* playScene = SceneManager::GetPlayScene();

        for (size_t row = 0; row < _COLLIDER_LAYER; row++)
        {
            for (size_t col = 0; col < _COLLIDER_LAYER; col++)
            {
                if (mMatrix[row] & (1 << col)) {
                    //충돌인지 아닌지 검사
                    LayerCollision(playScene, (eColliderLayer)row, (eColliderLayer)col);
                }
            }
        }
    }

    void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
    {
        /*
            ㅁㅁㅁㅁ
            x ㅁㅁㅁ
            x x ㅁㅁ
            x x x ㅁ
            -> 대각선기준 오른쪽만 사용
        */
        //더 작은 숫자를 행, 더 큰 숫자를 열로
        UINT row = 0;
        UINT col = 0;

        UINT iLeft = (UINT)left;
        UINT iRight = (UINT)right;

        if (iLeft < iRight)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        if (value == true)
            mMatrix[row] |= (1 << col);
        else
            mMatrix[row] &= ~(1 << col);

    }

    void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
    {
        // 모든 left 오브젝트들과 right 들을 가져와서 비교해줘야 한다.
        std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
        std::vector<GameObject*>& rights = scene->GetGameObjects(right);

        for (auto leftObject : lefts)
        {
            if (leftObject->GetComponent<Collider>() == nullptr)
                continue;

            for (auto rightObject : rights)
            {
                if (rightObject->GetComponent<Collider>() == nullptr)
                    continue;

                if (leftObject == rightObject)
                    continue;

                if (Intersect(leftObject->GetComponent<Collider>(), rightObject->GetComponent<Collider>())) ///충돌체크
                {
                    // 충돌
                    int a = 0;
                    leftObject->GetComponent<Collider>()->SetColor(RGB(255, 0, 0));
                    rightObject->GetComponent<Collider>()->SetColor(RGB(255, 0, 0));
                }
                else
                {
                    // 충돌X
                    int a = 0;
                    leftObject->GetComponent<Collider>()->SetColor(RGB(0, 255, 0));
                    rightObject->GetComponent<Collider>()->SetColor(RGB(0, 255, 0));
                }
            }
        }
    }

    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        Vector2 leftPos = left->GetPos();
        Vector2 leftScale = left->GetScale();

        Vector2 rightPos = right->GetPos();
        Vector2 rightScale = right->GetScale();

        if (fabs(leftPos.x - rightPos.x) < fabs(leftScale.x / 2.0f + rightScale.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < fabs(leftScale.y / 2.0f + rightScale.y / 2.0f))
        {
            return true;
        }

        return false;
    }
}